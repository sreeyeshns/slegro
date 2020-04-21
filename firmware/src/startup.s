/* Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs */
Mode_USR	= 	0x10
Mode_FIQ	=	0x11
Mode_IRQ	=	0x12
Mode_SVC	=	0x13
Mode_ABT	=	0x17
Mode_UND	=	0x1B
Mode_SYS	=	0x1F

I_Bit		=	0x80	/* when I bit is set, IRQ is disabled */
F_Bit		=	0x40	/* when F bit is set, FIQ is disabled */

	.text
	.arm
	.global _start
	.func	_start
_start:
	B	_reset				/* Reset vector */
	B	_loop				/* Undefined Instruction */
	B	_loop				/* Software Interrupt */
	B	_loop				/* Prefetch Abort */
	B	_loop				/* Data Abort */
	NOP						/* Reserved */
	LDR pc, [pc, #-0x0FF0]	/* VicVectAddr */
	/* LDR pc, _fiq_addr */
	B	_loop				/* FIQ Handler */
_reset:
/* Enable FIQ and IRQ */
	MSR CPSR_c,#(Mode_IRQ | I_Bit | F_Bit)
	LDR SP, =__IRQ_stack_top__
	MSR CPSR_c,#Mode_SVC

/* Relocate the .data section (copy from ROM to RAM) */
	LDR	r0,=__data_load__
	LDR	r1,=__data_start__
	LDR	r2,=__data_end__
_l1:
	CMP	r1,r2
	LDMLTIA	r0!,{r3}
	STMLTIA r1!,{r3}
	BLT	_l1

	/* Clear the .bss section (zero init) */
	LDR	r1,=__bss_start__
	LDR	r2,=__bss_end__
	MOV	r3,#0
_l2:
	CMP	r1,r2
	STMLTIA r1!,{r3}
	BLT	_l2
	
	LDR	sp,=__stack_end__
	LDR	FP,=__stack_end__
	LDR	r0,=main
	MOV	lr,pc
	BX	r0
_loop:
	B	_loop

/* _fiq_addr:
	.word VIC_FIQ_handler
*/
	.endfunc
	.end
