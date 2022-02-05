# x86-64 asm test
.file "asm.s"
.global	asm_int_add

.text 
asm_int_add:
	# prolog
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	subq	$12, %rsp

	# add
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	addl	%esi, %edi
	movl	%edi, -12(%rbp)

	# return value
	movl	-12(%rbp), %eax

	# epilog
	leave 
	ret

