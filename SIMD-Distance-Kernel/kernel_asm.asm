section .text

global distance_kernel_asm

; void distance_kernel_asm(
;     int n,
;     const double *x1,
;     const double *x2,
;     const double *y1,
;     const double *y2,
;     double *z
; )

distance_kernel_asm:

    ; Check if n <= 0
    test ecx, ecx
    jle .done

    ; Get the 5th and 6th arguments from the stack
    mov r10, [rsp + 40]     ; y2
    mov r11, [rsp + 48]     ; z

    xor eax, eax            ; i = 0

.loop:

    ; Calculate dx = x2[i] - x1[i]
    movsd xmm0, [r8 + rax*8]
    subsd xmm0, [rdx + rax*8]

    ; Calculate dx squared
    mulsd xmm0, xmm0

    ; Calculate dy = y2[i] - y1[i]
    movsd xmm1, [r10 + rax*8]
    subsd xmm1, [r9 + rax*8]

    ; Calculate dy squared
    mulsd xmm1, xmm1

    ; Calculate dx² + dy²
    addsd xmm0, xmm1

    ; Calculate square root
    sqrtsd xmm0, xmm0

    ; Store result in z[i]
    movsd [r11 + rax*8], xmm0

    ; Increment i
    inc rax

    ; Repeat while i < n
    cmp eax, ecx
    jl .loop

.done:
    ret
