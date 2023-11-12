.intel_syntax noprefix

.text
	.globl invoke, _start
	.extern main

	_start:
    	pop rdi
    	mov rsi, rsp
    	and rsp, -16
    	call main
		mov rdi, rax
		mov rax, 60
		syscall
    	ret
    
	invoke: /* invoke(id, a, b, c, d, e, f) */
	    mov rax, rdi
	    mov rdi, rsi
	    mov rsi, rdx
	    mov rdx, rcx
	    mov r10, r8
	    mov  r8, r9
	    mov  r9, [rsp - 8]
	    syscall
	    ret
