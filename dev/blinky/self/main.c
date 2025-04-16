#include <stddef.h>
#include <stdbool.h>
#include "app.h"

void app(void) {
	for (;;) {
		led_gpio_set(true);
		spin(999);
		led_gpio_set(false);
		spin(999);
	}
}

int main(void) {
	led_rcc_init();
	led_gpio_init();
	led_gpio_set(true);
	app();

	for (;;) (void) 0;
	return 0;
}

__attribute__((naked, noreturn)) void _reset(void) {
	extern long _sdata, _edata, _sidata;
	extern long _sbss, _ebss;

	long *cur = &_sidata; 
	long *dst = &_sdata;
	while (cur < &_edata) {
		*dst = *cur;
		++cur;
		++dst;
	}


	cur = NULL;
	cur = &_sbss;
	while (cur < &_ebss) {
		*cur = 0;
		++cur;
	}
	
	main();
	for (;;) (void) 0;

}

extern void _estack(void);

__attribute__((section(".vectors"))) void (* const _vector_table[16 + 91])(void) = {
		_estack, _reset,
	};
