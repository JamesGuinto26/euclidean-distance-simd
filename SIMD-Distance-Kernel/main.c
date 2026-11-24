
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include "kernel.h"

// Convert timer ticks into seconds
double get_elapsed_time(
    LARGE_INTEGER start,
    LARGE_INTEGER end,
    LARGE_INTEGER frequency
) {
    return (double)(end.QuadPart - start.QuadPart)
        / (double)frequency.QuadPart;
}

// Function pointer for both C and ASM kernels
typedef void (*KernelFunction)(
    int,
    const double*,
    const double*,
    const double*,
    const double*,
    double*
    );

// Benchmark one kernel
void benchmark_kernel(
    const char* name,
    KernelFunction kernel,
    int n,
    const double* x1,
    const double* x2,
    const double* y1,
    const double* y2,
    double* z,
    LARGE_INTEGER frequency
) {
    LARGE_INTEGER start, end;
    double total_time = 0.0;

    // Warm-up execution
    kernel(n, x1, x2, y1, y2, z);

    // Perform 30 timed executions
    for (int run = 0; run < 30; run++) {

        QueryPerformanceCounter(&start);

        kernel(n, x1, x2, y1, y2, z);

        QueryPerformanceCounter(&end);

        total_time += get_elapsed_time(start, end, frequency);
    }

    double average = (total_time / 30.0) * 1000.0;

    printf("%s average: %.6f ms\n", name, average);
}

int main(void) {

    // =====================================
    // PART 1: CORRECTNESS TEST
    // =====================================

    int n = 4;

    // Values from the specifications
    double x1[] = { 1.5, 4.0, 3.5, 2.0 };
    double x2[] = { 3.0, 2.5, 2.5, 1.0 };

    double y1[] = { 4.0, 3.0, 3.5, 3.0 };
    double y2[] = { 2.0, 2.5, 1.0, 1.5 };

    double result_c[4];
    double result_asm[4];

    distance_kernel_c(n, x1, x2, y1, y2, result_c);
    distance_kernel_asm(n, x1, x2, y1, y2, result_asm);

    printf("C Implementation vs NASM Implementation\n\n");

    for (int i = 0; i < n; i++) {

        printf("Index %d:\n", i);
        printf("C result:    %.6f\n", result_c[i]);
        printf("ASM result:  %.6f\n", result_asm[i]);

        if (fabs(result_c[i] - result_asm[i]) < 0.000001) {
            printf("Status: MATCH\n\n");
        }
        else {
            printf("Status: MISMATCH\n\n");
        }
    }

    // =====================================
    // PART 2: PERFORMANCE BENCHMARK
    // =====================================

    LARGE_INTEGER frequency;

    if (!QueryPerformanceFrequency(&frequency)) {
        printf("High-resolution timer unavailable.\n");
        return 1;
    }

    int sizes[] = {
        1 << 20,
        1 << 24,
        1 << 28
    };

    int number_of_sizes = 3;

    printf("\n========== PERFORMANCE BENCHMARK ==========\n");

    for (int s = 0; s < number_of_sizes; s++) {

        int n = sizes[s];

        printf("\nVector size: %d\n", n);

        // Allocate memory for five arrays
        double* x1 = malloc((size_t)n * sizeof(double));
        double* x2 = malloc((size_t)n * sizeof(double));
        double* y1 = malloc((size_t)n * sizeof(double));
        double* y2 = malloc((size_t)n * sizeof(double));
        double* z = malloc((size_t)n * sizeof(double));

        // Check allocation
        if (!x1 || !x2 || !y1 || !y2 || !z) {

            printf("Insufficient memory. Skipping this size.\n");

            free(x1);
            free(x2);
            free(y1);
            free(y2);
            free(z);

            continue;
        }

        // Initialize input arrays
        for (int i = 0; i < n; i++) {
            x1[i] = 1.5;
            x2[i] = 3.0;
            y1[i] = 4.0;
            y2[i] = 2.0;
        }

        // Benchmark C implementation
        benchmark_kernel(
            "C",
            distance_kernel_c,
            n, x1, x2, y1, y2, z, frequency
        );

        // Benchmark ASM implementation
        benchmark_kernel(
            "ASM",
            distance_kernel_asm,
            n, x1, x2, y1, y2, z, frequency
        );

        // Release allocated memory
        free(x1);
        free(x2);
        free(y1);
        free(y2);
        free(z);
    }

    printf("\n========== BENCHMARK COMPLETE ==========\n");

    return 0;
}
