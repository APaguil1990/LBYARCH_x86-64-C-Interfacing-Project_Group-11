; Paguiligan, James Archer B. 
; Bibon, Kyle Adrian L. 
; S15 - LBYARCH (Group 11)

section .data 
    ; Declare constant values
    one_k dq 1000.0 
    one_s dq 3600.0

section .text
global accelerations

accelerations:
    xor rbx, rbx                            ; Initialize counter

loop: 
    cmp rbx, rcx                            ; Compare loop counter with n_cars
    jge exit                                ; Exit if rbx >= n_cars 
    
    ; Calculate row index for input_matrix 
    mov rax, rbx
    imul rax, 3                             ; rax = rbx * 3 (row index for input_matrix) 
    
    ; Load Initial Velocity (Vi), Final Velocity (Vf), and Time (T) 
    movq xmm0, qword [rdx + rax * 8]        ; xmm0 = Vi (KM/H) 
    movq xmm1, qword [rdx + rax * 8 + 8]    ; xmm1 = Vf (KM/H) 
    movq xmm2, qword [rdx + rax * 8 + 16]   ; xmm2 = T (Time in seconds) 
    
    ; Convert Vi and Vf from KM/H to M/S 
    movq xmm3, qword [one_k]                ; xmm3 = 1000.0 
    movq xmm4, qword [one_s]                ; xmm4 = 3600.0 
    
    divsd xmm0, xmm4                        ; Vi (KM/H) / 3600 
    mulsd xmm0, xmm3                        ; Vi (M/S) 
    divsd xmm1, xmm4                        ; Vf (KM/H) / 3600 
    mulsd xmm1, xmm3                        ; Vf (M/S) 
    
    ; Compute acceleration: (Vf - Vi) / T 
    subsd xmm1, xmm0                        ; xmm1 = Vf - Vi 
    divsd xmm1, xmm2                        ; xmm1 = (Vf - Vi) / T 
    
    ; Round to nearest integer 
    roundsd xmm1, xmm1, 0 
    
    ; Convert to integer and store in output_result 
    cvttsd2si eax, xmm1                     ; eax = (int) xmm1 
    mov dword [r8 + rbx * 4], eax 
    inc rbx 
    jmp loop 

exit: 
    ret
    