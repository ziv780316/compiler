expr_O2_gcse:
.LFB44:
	.cfi_startproc
	movsd	(%rdi), %xmm2
	movapd	%xmm2, %xmm0
	call	f1
	movapd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	movapd	%xmm2, %xmm0
	call	f2
	movapd	%xmm0, %xmm2
	movsd	(%rdi), %xmm0
	call	f2
	mulsd	.LC2(%rip), %xmm1
	mulsd	%xmm2, %xmm0
	mulsd	%xmm1, %xmm0
	divsd	.LC8(%rip), %xmm0
	movsd	%xmm0, (%rsi)
	ret
