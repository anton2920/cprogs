	.file	"array5.c"
	.section	.rodata
.LC0:
	.string	"Max = %d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$48, %esp
	movl	$1, 28(%esp)
	movl	$2, 32(%esp)
	movl	$3, 36(%esp)
	movl	$4, 40(%esp)
	movl	$5, 44(%esp)
	movl	$0, 24(%esp)
	movl	$1, 20(%esp)
	jmp	.L2
.L4:
	movl	20(%esp), %eax
	leal	0(,%eax,4), %edx
	leal	28(%esp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	20(%esp), %eax
	addl	$1073741823, %eax
	leal	0(,%eax,4), %ecx
	leal	28(%esp), %eax
	addl	%ecx, %eax
	movl	(%eax), %eax
	cmpl	%eax, %edx
	jle	.L3
	movl	20(%esp), %eax
	leal	0(,%eax,4), %edx
	leal	28(%esp), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	%eax, 24(%esp)
.L3:
	addl	$1, 20(%esp)
.L2:
	cmpl	$4, 20(%esp)
	jle	.L4
	movl	24(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	$0, (%esp)
	call	exit
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.4) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
