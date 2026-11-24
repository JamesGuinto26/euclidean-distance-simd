#ifndef KERNEL_H
#define KERNEL_H

void distance_kernel_c(int n, const double* x1, const double* x2, const double* y1, const double* y2, double* z);

void distance_kernel_asm(int n, const double* x1, const double* x2, const double* y1, const double* y2, double* z);

#endif
