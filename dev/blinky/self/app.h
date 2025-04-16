#ifndef _APP_H_
#define _APP_H_

#include <inttypes.h>
#include <stdbool.h>

/* ==================== GPIO ==================== */
#define PIN(bank, num) (uint16_t)( ((bank - 'A') << 8) | (0xFF & num) )
#define PINNO(pin) (pin & 0xFF)
#define PINBANK(pin) (pin >> 8)

enum { GPIO_INPUT_MODE, GPIO_OUTPUT_MODE, GPIO_AF_MODE, GPIO_ANALOG_MODE };
struct gpio {
	volatile uint32_t MODER, OTYPER, OSPEEDR, PUPDR, IDR, ODR, BSRR, LCKR, AFR[2];	
};
#define GPIO(pin) ((struct gpio*)((PINBANK(pin) * 0x400) + 0x40020000))

#define LED PIN('A', 5)
static inline void led_gpio_init() {
	uint16_t led = LED;
	struct gpio* gpio = GPIO(PINBANK(led));
	gpio->MODER &= ~(3UL << (2 * PINNO(led)));
	gpio->MODER |= ((3UL | GPIO_OUTPUT_MODE) << (2 * PINNO(led)));
}

static inline void led_gpio_set(bool mode) {
	uint16_t led = LED;
	struct gpio* gpio = GPIO(PINBANK(led));
	if (mode) {
		gpio->BSRR |= (1UL << PINNO(LED));
	} else {
		gpio->BSRR |= (1UL << PINNO(LED)) + (0x10);
	}
}


/* ==================== RCC ==================== */
struct rcc {
  volatile uint32_t CR, PLLCFGR, CFGR, CIR, AHB1RSTR, AHB2RSTR, AHB3RSTR,
      RESERVED0, APB1RSTR, APB2RSTR, RESERVED1[2], AHB1ENR, AHB2ENR, AHB3ENR,
      RESERVED2, APB1ENR, APB2ENR, RESERVED3[2], AHB1LPENR, AHB2LPENR,
      AHB3LPENR, RESERVED4, APB1LPENR, APB2LPENR, RESERVED5[2], BDCR, CSR,
      RESERVED6[2], SSCGR, PLLI2SCFGR;
};
#define RCC ((struct rcc*)(0x40023800))

static inline void led_rcc_init() {
	RCC->AHB1ENR |= (1UL << (0));
}




/* ==================== OTHER ==================== */
static inline void spin(volatile uint32_t val) {
	while (val--) (void) 0;
}


#endif /* _APP_H_ */
