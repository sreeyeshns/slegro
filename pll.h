#ifndef	_PPL_H
#define	_PPL_H

#define	PLLCON	(*(volatile unsigned long *) 0xE01FC080)
#define	PLLCFG	(*(volatile unsigned long *) 0xE01FC084)
#define	PLLSTAT	(*(const volatile unsigned long *) 0xE01FC088)
#define	PLLFEED	(*(volatile unsigned long *) 0xE01FC08C)

void init_pll(void);
#endif
