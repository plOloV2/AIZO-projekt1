.global BubbleSortASM

BubbleSortASM:
    // Inputs:
    // X0 - array pointer
    // W1 - array size (n)
    
    sub     w2, w1, #1             // new_limit = n - 1
    cmp     w2, #0                 // Handle n <= 1 cases
    b.le    .exit

.outer_loop:
    mov     w3, #0                 // last_swap = 0
    mov     w4, #0                 // j = 0

.inner_loop:
    cmp     w4, w2                 // Compare j with new_limit
    b.ge    .end_inner_loop        // Exit inner loop if j >= new_limit
    
    // Load arr[j] and arr[j+1]
    ldr     w5, [x0, w4, sxtw #2]  // w5 = arr[j]
    add     w6, w4, #1             // w6 = j+1
    ldr     w7, [x0, w6, sxtw #2]  // w7 = arr[j+1]
    
    cmp     w5, w7
    b.le    .no_swap

    // Perform swap
    str     w7, [x0, w4, sxtw #2]  // arr[j] = w7
    str     w5, [x0, w6, sxtw #2]  // arr[j+1] = w5
    mov     w3, w4                 // Update last_swap to j

.no_swap:
    add     w4, w4, #1             // j++
    b       .inner_loop

.end_inner_loop:
    mov     w2, w3                 // Update new_limit with last_swap
    cbnz    w2, .outer_loop        // Continue outer loop if new_limit > 0

.exit:
    ret
