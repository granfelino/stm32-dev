#ifndef _START_H
#define _START_H


#include <stddef.h>
#include <inttypes.h>

void _estack(void);

__attribute__((naked, noreturn)) void _reset(void);

__attribute__((section(".vectors"))) void (*const vector_table[16 + 91])(void) = {
	_estack,
	_reset
};


#endif      /* _START_H */
