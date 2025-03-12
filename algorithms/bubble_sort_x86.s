.text
.globl QBubbleSort
.type QBubbleSort, @function

QBubbleSort:
    pushl   %ebp
    movl    %esp, %ebp
    pushl   %esi
    pushl   %edi
    pushl   %ebx

    /* Load parameters */
    movl    8(%ebp), %esi   /* esi = arr */
    movl    12(%ebp), %ecx  /* ecx = n */

    /* Initialize new_limit = n-1 */
    leal    -1(%ecx), %edi  /* edi = new_limit */

do_loop:
    xorl    %ebx, %ebx      /* last_swap = 0 */
    xorl    %eax, %eax      /* j = 0 */

for_loop:
    cmpl    %edi, %eax      /* Compare j with new_limit */
    jge     end_for

    /* Load and compare elements */
    movl    (%esi,%eax,4), %edx    /* arr[j] */
    movl    4(%esi,%eax,4), %ecx   /* arr[j+1] */
    cmpl    %ecx, %edx
    jle     no_swap

    /* Swap elements */
    movl    %ecx, (%esi,%eax,4)
    movl    %edx, 4(%esi,%eax,4)
    movl    %eax, %ebx      /* Update last_swap */

no_swap:
    incl    %eax            /* j++ */
    jmp     for_loop

end_for:
    movl    %ebx, %edi      /* Update new_limit */
    testl   %edi, %edi
    jg      do_loop         /* Loop while new_limit > 0 */

    popl    %ebx
    popl    %edi
    popl    %esi
    popl    %ebp
    ret
    