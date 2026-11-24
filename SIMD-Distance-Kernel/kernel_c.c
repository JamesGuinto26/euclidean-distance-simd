#include <math.h>
#include "kernel.h"

void distance_kernel_c(int n, const double* x1, const double* x2, const double* y1, const double* y2, double* z) {
    
    for (int i = 0; i < n; i++) {

        double dx = x2[i] - x1[i];
        double dy = y2[i] - y1[i];

        z[i] = sqrt(dx * dx + dy * dy);
    }
}
