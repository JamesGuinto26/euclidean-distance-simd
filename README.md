# SIMD Distance Kernel: C and x86-64 Assembly Performance Comparison

**Submitted by:** James Ryan K. Guinto of S30E


## 1. Introduction

This programming project implements and evaluates a Euclidean distance kernel between the coordinate points across two vectors using two approaches which are the C language and x86-64 Assembly using NASM.

The purpose is to calculate the distance between corresponding points in a two-dimensional coordinate system. Both implementations perform the same mathematical operation and uses the same formula, which allows for execution and execution performance comparisons.

The Assembly implementation uses scalar SIMD instructions to perform floating-point calculations.

## 2. Project Objectives

- Implement the Euclidean distance calculation using C.
- Implement the same Euclidean distance calculation using x86-64 Assembly and NASM.
- Verify that both implementations produce matching results.
- Measure execution time using different vector sizes.
- Compare the performance of both implementations.

## 3. Mathematical Formula

The Euclidean distance between two points is calculated using:

![Euclidean Distance Formula](images/euclideanDistance.jpg)

Which is used by the kernel during calculations for each array index \(i\).
The resulting distance is stored in the output array `z`.

## 4. Project Structure

```text
SIMD-Distance-Kernel/
│
├── SIMD-Distance-Kernel.slnx
├── images/
├── .gitignore
├── README.md
│
└── SIMD-Distance-Kernel/
    ├── main.c
    ├── kernel.h
    ├── kernel_c.c
    ├── kernel_asm.asm
    ├── SIMD-Distance-Kernel.vcxproj
    └── SIMD-Distance-Kernel.vcxproj.filters
```

### File Descriptions

| File | Description |
|---|---|
| `main.c` | Performs correctness testing and performance benchmarking. |
| `kernel.h` | Contains function declarations for both C and Assembly implementations. |
| `kernel_c.c` | Implements the Euclidean distance calculation in C. |
| `kernel_asm.asm` | Implements the Euclidean distance calculation in x86-64 Assembly and scalar SIMD instructions. |
| `.slnx` | Visual Studio solution file. |
| `.vcxproj` | Visual Studio project configuration. |


## 5. Implementation

### 5.1 C Implementation

The C implementation uses a loop to process each element of the input arrays. It calculates the differences between the corresponding X and Y coordinates, squares the differences, adds them together, and obtains the square root using the `sqrt()` function from the C math library.

### 5.2 x86-64 Assembly Implementation

The Assembly implementation of the euclidean distance calculation uses NASM syntax and scalar SSE2 instructions for double-precision floating-point calculations.

| Instruction | Purpose |
|---|---|
| `MOVSD` | Moves a scalar double-precision value. |
| `SUBSD` | Subtracts scalar double-precision values. |
| `MULSD` | Multiplies scalar double-precision values. |
| `ADDSD` | Adds scalar double-precision values. |
| `SQRTSD` | Calculates the square root of a scalar value. |

The XMM registers are used to perform the floating-point calculations. The Assembly function processes the arrays using a loop and stores each calculated distance in the output array.

