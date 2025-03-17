.global BubbleSortASM
.text

BubbleSortASM:
    # Inputs:
    # rdi - array pointer
    # esi - array size (n)
    
    pushq   %rbp
    movq    %rsp, %rbp
    pushq   %rbx          # Save callee-saved registers
    
    # Initialize new_limit = n-1
    movl    %esi, %r8d    # r8d = n
    decl    %r8d           # r8d = new_limit (n-1)
    jle     .exit          # Exit if array size <= 1

.outer_loop:
    xorl    %r9d, %r9d    # last_swap = 0
    xorl    %ecx, %ecx    # j = 0

.inner_loop:
    cmpl    %r8d, %ecx    # Compare j with new_limit
    jge     .end_inner
    
    # Load and compare adjacent elements
    movl    (%rdi,%rcx,4), %eax   # eax = arr[j]
    movl    4(%rdi,%rcx,4), %ebx  # ebx = arr[j+1]
    
    cmpl    %ebx, %eax
    jle     .no_swap
    
    # Perform swap
    movl    %ebx, (%rdi,%rcx,4)   # arr[j] = ebx
    movl    %eax, 4(%rdi,%rcx,4)  # arr[j+1] = eax
    movl    %ecx, %r9d            # last_swap = j

.no_swap:
    incl    %ecx           # j++
    jmp     .inner_loop

.end_inner:
    movl    %r9d, %r8d    # new_limit = last_swap
    testl   %r8d, %r8d
    jg      .outer_loop    # Continue if new_limit > 0

.exit:
    popq    %rbx
    popq    %rbp
    ret
