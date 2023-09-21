
section .data
    const1 dq 1.0
    const2 dq 2.0
    const3 dq 3.0
    const0 dq 0.0
    const06 dq 0.66666666666666
section .text
GLOBAL f1
f1: ;f1(x) = exp(x)+2
    push ebp
    mov ebp, esp
    finit
    fld  qword[ebp+8]
    fldl2e
    fmul
    fld     st0
    frndint
    fsub    st1, st0
    fxch    st1
    f2xm1
    fld1
    fadd
    fscale
    fld qword[const2]
    faddp
    mov esp, ebp
    pop ebp
    ret
    
GLOBAL f2
f2:; f2 = -1/x
    push ebp
    mov ebp, esp
    finit
    fld qword[const1]
    fld qword[ebp+8]
    fdivp ;st1, st0
    FCHS
    mov esp, ebp
    pop ebp
    ret
    
GLOBAL f3
f3:; -2(x+1)/3
    push ebp
    mov ebp, esp
    finit
    fld qword[ebp+8]
    fld qword[const1]
    faddp
    fld qword[const06]
    fmulp
    fchs
    mov esp, ebp
    pop ebp
    ret
    
GLOBAL Derivative_f1

Derivative_f1:
    push ebp
    mov ebp, esp
    finit
    fld  qword[ebp+8]
    fldl2e
    fmul
    fld     st0
    frndint
    fsub    st1, st0
    fxch    st1
    f2xm1
    fld1
    fadd
    fscale
    mov esp, ebp
    pop ebp
    ret
    
GLOBAL Derivative_f2

Derivative_f2:
    push ebp
    mov ebp, esp
    
    finit
    fld qword[const1]
    fld qword[ebp+8]
    fld qword[ebp+8]

    fmulp st1, st0
    fdivp st1, st0
    mov esp, ebp
    pop ebp
    ret
    
GLOBAL Derivative_f3
Derivative_f3:
    push ebp
    mov ebp, esp
    finit
    fld qword[const2]
    fld qword[const3]
    fdivp st1, st0
    fchs    
    mov esp, ebp
    pop ebp
    ret
GLOBAL CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    mov eax, 4
    push dword[eax]
    call f1
    call f2
    call f3
    add esp, 4
    mov esp, ebp
    pop ebp
    ret
    
    