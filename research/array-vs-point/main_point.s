	.file	"main_point.cpp"
	.text
	.globl	_Z5pointPKcRKiRS_
	.def	_Z5pointPKcRKiRS_;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z5pointPKcRKiRS_
_Z5pointPKcRKiRS_:
.LFB0:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	movq	%r8, 32(%rbp)
	movq	24(%rbp), %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
.L5:
	movq	16(%rbp), %rax
	leaq	1(%rax), %rdx
	movq	%rdx, 16(%rbp)
	movzbl	(%rax), %edx
	movq	32(%rbp), %rax
	movzbl	(%rax), %eax
	cmpb	%al, %dl
	sete	%al
	testb	%al, %al
	je	.L2
	movq	24(%rbp), %rax
	movl	(%rax), %eax
	subl	-4(%rbp), %eax
	jmp	.L3
.L2:
	movl	-4(%rbp), %eax
	leal	-1(%rax), %edx
	movl	%edx, -4(%rbp)
	testl	%eax, %eax
	setne	%al
	testb	%al, %al
	je	.L4
	jmp	.L5
.L4:
	movl	$-1, %eax
.L3:
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "hello\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB1:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	call	__main
	movb	$111, -9(%rbp)
	movl	$5, -16(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, -8(%rbp)
	leaq	-9(%rbp), %rcx
	leaq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rcx, %r8
	movq	%rax, %rcx
	call	_Z5pointPKcRKiRS_
	movl	$0, %eax
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (tdm64-1) 10.3.0"
