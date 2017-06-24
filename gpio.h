#ifndef _GPIO_H
#define _GPIO_H

#include <stdint.h>

#define PINSEL0 (*(volatile uint32_t *) 0xE002C000)
#define PINSEL1 (*(volatile uint32_t *) 0xE002C004)
#define PINSEL2 (*(volatile uint32_t *) 0xE002C014)

#define IO0PIN  (*(volatile uint32_t *) 0xE0028000)
#define IO0SET  (*(volatile uint32_t *) 0xE0028004)
#define IO0DIR  (*(volatile uint32_t *) 0xE0028008)
#define IO0CLR  (*(volatile uint32_t *) 0xE002800C)
#endif
