.globl _start
	
_start:
	pop %rdi  		# argc
	movq %rsp, %rsi 	# argv
	lea -8(%rsp),%rsp      	# Make sure the return address doesn't clobber argv
	call main
	mov %rax, %rdi		# Only argument to exit() is the return value of main().
	call exit
