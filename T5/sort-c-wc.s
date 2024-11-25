	.file	"sort-c-wc.c"
	.option nopic
	.attribute arch, "rv32i2p0_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	w_count
	.type	w_count, @function
w_count:
	mv	a5,a0   		# // p = a
	lbu	a4,0(a0)		# // 
	beq	a4,zero,.L8		# // si p es igual a 0 (array vacío) salta a L8 
	li	a0,0			# // count = 0
	li	a3,32			# // a3 = ' '
	j	.L7				# // salta al label L7
.L12:
	lbu	a4,0(a5)		# // lee el carácter
	beq	a4,a3,.L4		# // si el carácter es ' ' salta al label L4
.L5:
	beq	a4,zero,.L4		# // si el carácter es 0, salta al label L4
	addi	a5,a5,1		# // avanza un char en el string
	lbu	a4,0(a5)		# // carga el valor del char
	bne	a4,a3,.L5		# // si el char es distinto de ' ', comienza un loop
.L4:
	addi	a0,a0,1		# // suma uno al contador
.L6:
	lbu	a4,0(a5)		# // carga el char del string
	beq	a4,zero,.L11	# // si el carácter es 0, salta al label L11
.L7:
	bne	a4,a3,.L12		# // si *p != ' ' salta al label L12
	addi	a5,a5,1		# // sino es ' ', avanza un char del string
	j	.L6				# // salta al label L6
.L11:
	ret					# // retorna el contador
.L8:
	li	a0,0  		# // a0 = 0
	ret				# // return 0, palabra vacía
	.size	w_count, .-w_count
	.align	2
	.globl	sort
	.type	sort, @function
sort:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	sw	s1,20(sp)
	sw	s2,16(sp)
	sw	s3,12(sp)
	sw	s4,8(sp)
	sw	s5,4(sp)
	slli	s4,a1,2
	addi	s4,s4,-4
	add	s4,a0,s4
	bgeu	a0,s4,.L13
	mv	s5,a0
	mv	s0,a0
	j	.L17
.L15:
	sw	s3,0(s0)
	sw	s2,4(s0)
	mv	s0,s5
.L17:
	lw	s2,0(s0)
	mv	a0,s2
	call	w_count
	mv	s1,a0
	lw	s3,4(s0)
	mv	a0,s3
	call	w_count
	bgt	s1,a0,.L15
	addi	s0,s0,4
	bgtu	s4,s0,.L17
.L13:
	lw	ra,28(sp)
	lw	s0,24(sp)
	lw	s1,20(sp)
	lw	s2,16(sp)
	lw	s3,12(sp)
	lw	s4,8(sp)
	lw	s5,4(sp)
	addi	sp,sp,32
	jr	ra
	.size	sort, .-sort
	.ident	"GCC: (GNU) 11.1.0"
