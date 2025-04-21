#ifndef _GPIO_REG
#define _GPIO_REG

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
    uint32_t MODER;
    uint32_t SPEEDR;
    uint32_t PUPDR;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t BSRR;
    uint32_t LCKR;
    uint32_t AFR[2];
};


/* USAGE EXAMPLE: GPIO_A->MODER |= (1U << 10) */
#define GPIO_A          ((volatile struct gpio *)(GPIO_A_BASE))


#endif      /* _GPIO_REG */
