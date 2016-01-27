	.text
	.arm
	.global _start
	.func	_start
_start:
	
/* Relocate the .data section (copy from ROM to RAM) */
	LDR	r0,=__data_load__
	LDR	r1,=__data_start__
	LDR	r2,=__data_end__
l1:
	CMP	r1,r2
	LDMLTIA	r0!,{r3}
	STMLTIA r1!,{r3}
	BLT	l1

	/* Clear the .bss section (zero init) */
	LDR	r1,=__bss_start__
	LDR	r2,=__bss_end__
	MOV	r3,#0
l2:
	CMP	r1,r2
	STMLTIA r1!,{r3}
	BLT	l2
	
	LDR	sp,=__stack_end__
	LDR	FP,=__stack_end__
	LDR	r0,=main
	MOV	lr,pc
	BX	r0

	.endfunc
	.end
