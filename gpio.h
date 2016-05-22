#ifndef	_GPIO_H
#define	_GPIO_H

#define PINSEL0	(*(volatile unsigned long *) 0xE002C000)
#define PINSEL1	(*(volatile unsigned long *) 0xE002C004)
#define PINSEL2	(*(volatile unsigned long *) 0xE002C014)

#define IO0SET	(*(volatile unsigned long *) 0xE0028004)
#define IO0DIR	(*(volatile unsigned long *) 0xE0028008)
#endif
