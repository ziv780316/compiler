expr_O0:
.LFB45:
	.cfi_startproc
	subq	$48, %rsp
	.cfi_def_cfa_offset 56
	movq	%rdi, 24(%rsp)
	movq	%rsi, 16(%rsp)
	movq	24(%rsp), %rax
	movq	(%rax), %rax
	movq	%rax, (%rsp)
	movsd	(%rsp), %xmm0
	call	f1
	movsd	%xmm0, (%rsp)
	movq	24(%rsp), %rax
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)
	movsd	8(%rsp), %xmm0
	call	f1
	mulsd	(%rsp), %xmm0
	movsd	%xmm0, 32(%rsp)
	movq	24(%rsp), %rax
	movq	(%rax), %rax
	movq	%rax, (%rsp)
	movsd	(%rsp), %xmm0
	call	f2
	movsd	%xmm0, (%rsp)
	movq	24(%rsp), %rax
	movq	(%rax), %rax
	movq	%rax, 8(%rsp)
	movsd	8(%rsp), %xmm0
	call	f2
	mulsd	(%rsp), %xmm0
	movsd	%xmm0, 40(%rsp)
	movsd	32(%rsp), %xmm1
	movsd	.LC2(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	mulsd	40(%rsp), %xmm0
	movsd	.LC8(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movq	16(%rsp), %rax
	movsd	%xmm0, (%rax)
	nop
	addq	$48, %rsp
	.cfi_def_cfa_offset 8
	ret
