; Paguiligan, James Archer B. 
; Bibon, Kyle Adrian L. 
; S15 - LBYARCH (Group 11)

section .data 
    ; Declare constant values
    one_k dq 1000.0                         ; Conversion factor for kilometers to meters (1 km = 1000 meters) 
    one_s dq 3600.0                         ; Conversion factor for hours to seconds (1 hr = 3600 seconds)

section .text
global accelerations

accelerations:
    xor rbx, rbx                            ; Initialize counter rbx = 0

loop: 
    cmp rbx, rcx                            ; Compare loop counter with total rows (rcx)
    jge exit                                ; Exit if rbx >= rcx (n_cars)
    
    ; Calculate row index for input_matrix 
    mov rax, rbx                            ; Compare loop counter (rbx) with total rows (rcx)
    imul rax, 3                             ; Multiply rax by 3 (each row has 3 values: Vi, Vf, T)
    
    ; Load Initial Velocity (Vi), Final Velocity (Vf), and Time (T) 
    movq xmm0, qword [rdx + rax * 8]        ; Load Vi (double, in km/h) into xmm0
    movq xmm1, qword [rdx + rax * 8 + 8]    ; Load Vf (double, in km/h) into xmm1
    movq xmm2, qword [rdx + rax * 8 + 16]   ; Load T (double, in seconds) into xmm2
    
    ; Convert Vi and Vf from KM/H to M/S 
    movq xmm3, qword [one_k]                ; Load conversion factor (1000.0) into xmm3
    movq xmm4, qword [one_s]                ; Load conversion factor (3600.0) into xmm3
    
    divsd xmm0, xmm4                        ; Convert Vi from km/h to m/s: Vi = Vi / 3600
    mulsd xmm0, xmm3                        ; Vi = Vi * 1000 
    divsd xmm1, xmm4                        ; Convert Vf from km/h to m/s: Vf = Vf / 3600
    mulsd xmm1, xmm3                        ; Vf = Vf * 1000
    
    ; Compute acceleration: (Vf - Vi) / T 
    subsd xmm1, xmm0                        ; Compute (Vf - Vi): xmm1 = Vf - Vi
    divsd xmm1, xmm2                        ; Compute accelerations: xmm1 = (Vf - Vi) / T
    
    ; Round to nearest integer 
    roundsd xmm1, xmm1, 0                   ; Round xmm1 to nearest integer
    
    ; Convert to integer and store in output_result 
    cvttsd2si eax, xmm1                     ; Convert floating-point value in xmm1 to an integer (eax)
    mov dword [r8 + rbx * 4], eax           ; Store result (eax) in output array at index rbx
    
    ; Increment loop counter and process next row
    inc rbx                                 ; Increment rbx to move to next row
    jmp loop                                ; Repeat the loop

exit: 
    ret                                     ; Return to caller
    