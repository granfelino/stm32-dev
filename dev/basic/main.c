#incldue <stddef.h>

int main(void) {
	return 0;
}

void _estack(void);

__attribute__((naked, noreturn)) void _reset(void) {
	extern void *_sbss, *_ebss;
	extern void *_sdata, *_edata, *_sidata;
	void *src, *dst, *cur;
	
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

__attribute__((section(".vectors"))) void (*const vector_table[16 + 91])(void) {
	_estack,
	_reset
}
