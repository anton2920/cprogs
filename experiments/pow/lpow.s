.section .text
.type lpow, @function
.globl lpow
lpow:
	# Initializing function's stack frame
	pushl %ebp
	movl %esp, %ebp

	# Main part
	fldl 16(%ebp) # Power
	fldl 8(%ebp) # Base

	fyl2x # power * lb(Base)

	fld %st(0)
	frndint
	fsub %st(0), %st(1)
	fxch %st(1)
	f2xm1
	fld1
	faddp
	fscale
	fstp %st(1)

	# Destroying function's stack frame
	movl %ebp, %esp
	popl %ebp
	ret
