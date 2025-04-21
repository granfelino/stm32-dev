#include <stddef.h>
#include <inttypes.h>

__attribute__((naked, noreturn)) void _reset(void) {
	extern uint32_t _sbss, _ebss;
	extern uint32_t _sdata, _edata, _sidata;
	uint32_t *src, *dst, *cur;
	
	for (cur = &_sbss; cur < &_ebss;) {
		*cur++ = 0;
	}
	cur = NULL;

	for (src = &_sidata, dst = &_sdata; dst < &_edata; ) {
		*dst = *src;
		++dst;
		++src;
	}
	src = NULL;
	dst = NULL;

	for (;;) (void) 0;
}
