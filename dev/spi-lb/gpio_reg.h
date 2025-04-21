#ifndef _GPIO_REG_H
#define _GPIO_REG_H

#include <inttypes.h>
#include "reg_util.h"



/* GPIOs used in SPI1 loopback device:
 * PA4 - NSS
 * PA5 - SCK
 * PA6 - MISO
 * PA7 - MOSI 
 * */

#define GPIO_A_BASE     (0x40020000UL)

struct gpio {
    volatile uint32_t MODER;
    volatile uint32_t SPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
};

/* USAGE EXAMPLE: GPIO_A->MODER |= (1U << 10) */
#define GPIO_A          ((volatile struct gpio *)(GPIO_A_BASE))


/* set GPIO to AF */
static inline void gpio_a_mode_set() {
    /* clearing */
    GPIO_A->MODER &= ~(0b11 << (2 * 4));
    GPIO_A->MODER &= ~(0b11 << (2 * 5));
    GPIO_A->MODER &= ~(0b11 << (2 * 6));
    GPIO_A->MODER &= ~(0b11 << (2 * 7));

    /* setting */
    GPIO_A->MODER |= (0b10 << (2 * 4));
    GPIO_A->MODER |= (0b10 << (2 * 5));
    GPIO_A->MODER |= (0b10 << (2 * 6));
    GPIO_A->MODER |= (0b10 << (2 * 7));
}


/* set GPIO speed to high */
static inline void gpio_a_speed_set() {
    /* clearing */
    GPIO_A->SPEEDR &= ~(0b11 << (2 * 4));
    GPIO_A->SPEEDR &= ~(0b11 << (2 * 5));
    GPIO_A->SPEEDR &= ~(0b11 << (2 * 6));
    GPIO_A->SPEEDR &= ~(0b11 << (2 * 7));

    /* setting */
    GPIO_A->SPEEDR |= (0b11 << (2 * 4));
    GPIO_A->SPEEDR |= (0b11 << (2 * 5));
    GPIO_A->SPEEDR |= (0b11 << (2 * 6));
    GPIO_A->SPEEDR |= (0b11 << (2 * 7));
}


/* set GPIO to neither PU nor PD */
static inline void gpio_a_pupd_set() {
    GPIO_A->PUPDR &= ~(0b11 << (2 * 4));
    GPIO_A->PUPDR &= ~(0b11 << (2 * 5));
    GPIO_A->PUPDR &= ~(0b11 << (2 * 6));
    GPIO_A->PUPDR &= ~(0b11 << (2 * 7));
}


/* set GPIO to AF5 (SPI1) */
static inline void gpio_a_af_set() {
    /* clearing */
    GPIO_A->AFR[0] &= ~(0xF << (4 * 4));
    GPIO_A->AFR[0] &= ~(0xF << (4 * 5));
    GPIO_A->AFR[0] &= ~(0xF << (4 * 6));
    GPIO_A->AFR[0] &= ~(0xF << (4 * 7));

    /* setting */
    GPIO_A->AFR[0] |= (0x5 << (4 * 4));
    GPIO_A->AFR[0] |= (0x5 << (4 * 5));
    GPIO_A->AFR[0] |= (0x5 << (4 * 6));
    GPIO_A->AFR[0] |= (0x5 << (4 * 7));
}


void gpio_setup();

#endif      /* _GPIO_REG_H */
