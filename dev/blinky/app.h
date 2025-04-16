#ifndef _APP_H_
#define _APP_H_

#include <inttypes.h>
#include <stdbool.h>


/* ===================== GPIO SECTION ===================== */
#define BIT(x) (1UL << (x))
#define PIN(bank, num) ((((bank) - 'A') << 8) | (num))
#define PINNO(pin) (pin & 255)
#define PINBANK(pin) (pin >> 8)

struct gpio {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
};
#define GPIO_ADDR (0x40020000) 
#define GPIO(bank) ((struct gpio *) ((PINBANK(bank) * 0x04) + GPIO_ADDR))

enum {
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT,
	GPIO_MODE_AF,
	GPIO_MODE_ANALOG
};

static inline void gpio_set_mode(uint16_t pin, uint8_t mode) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	int pinno = PINNO(pin);
	gpio->MODER &= ~(3U << (pinno * 2));
	gpio->MODER |= ((3U & mode) << (pinno * 2));
}

static inline void gpio_set_vol(uint16_t pin, bool mode) {
	struct gpio *gpio = GPIO(PINBANK(pin));
	int pinno = PINNO(pin);
	if (mode) {
		gpio->BSRR = (1UL << pinno);
	} else {
		gpio->BSRR = (1UL << pinno) << (0x10);
	}
}

static inline void spin(volatile uint32_t count) {
	while (count--) (void) 0;
}


/* ===================== RCC SECTION ===================== */
struct rcc {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	uint32_t RSRVD0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t RSRVD1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	uint32_t RSRVD2;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	uint32_t RSRVD3[2];
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t AHB3LPENR;
	uint32_t RSRVD4;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	uint32_t RSRVD5[2];
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	uint32_t RSRVD[2];
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t PLLSAICFGR;
	volatile uint32_t DCKCFGR;
	volatile uint32_t CKGATENR;
	volatile uint32_t DCKCFGR2;
};
#define RCC_ADDR (0x40023800)
#define RCC ((struct rcc *) RCC_ADDR)
#define RCC_BANK(x) ((uint8_t) (x - 'A'))

static inline void rcc_gpio_ahb1enr(uint16_t led, uint8_t mode) {
	switch(mode) {
		case 0:
		RCC->AHB1ENR &= ~(1UL << PINBANK(led));
		break;

		case 1:
		RCC->AHB1ENR |= (1UL << PINBANK(led));
		break;

		default:
		break;
	}
}



/* ===================== SYSTICK SECTION ===================== */
struct systick {
	volatile uint32_t STCSR;
	volatile uint32_t STRVR;
	volatile uint32_t STCVR;
	volatile uint32_t STCR;
};
#define SYSTICK_ADDR (0xE000E010)
#define SYSTICK ((struct systick *) SYSTICK_ADDR)
#define TICKS ((16000000 / 1000) - 1)

static inline void systick_init() {
	SYSTICK->STRVR   |= ((0xffffff) & TICKS);
	SYSTICK->STCVR = 0;
	SYSTICK->STCSR = (1UL << 0) | (1UL << 1) | (1UL << 2);
}



#endif /* _APP_H_ */
