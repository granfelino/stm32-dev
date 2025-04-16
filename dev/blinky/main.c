#include <stddef.h>
#include <inttypes.h>
#include <stdbool.h>
#include "app.h"

#define PERIOD (500)

static volatile uint32_t systick_count = 0;

void wait_for_switch(void) {
	volatile uint32_t now = systick_count;
	uint32_t next_switch_time = now + PERIOD;
	while (next_switch_time > now) {
		now = systick_count;
	}
}

void app() {
	uint16_t led = PIN('A', 5); 		/* specify the pin */
	rcc_gpio_ahb1enr(led, 1);		/* enable clock for the GPIOA BANK */
	gpio_set_mode(led, GPIO_MODE_OUTPUT);	/* set the LED pin to output mode */

	for (;;) {
		gpio_set_vol(led, true);
		wait_for_switch();
		gpio_set_vol(led, false);
		wait_for_switch();
	}
}

int main(void) {
	app();
	return 0;
}


void _estack(void);

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

	systick_init();				/* enable and configure the systick interrupt */

	main();
	for (;;) (void) 0;
}

void _systick(void) {
	systick_count++;
}

__attribute__((section(".vectors"))) void (*const vector_table[16 + 91])(void) = {
	_estack, 
	_reset,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	_systick,
};
