#ifndef _GPIO_RCC
#define _GPIO_RCC

#include <inttypes.h>
#include "reg_util.h"

/* RCCs used in SPI1 loopback device: 
 * RCC_AHB1ENR - GPIOA
     + Bit 0
     + GPIOAEN: IO port A clock enable
     + This bit is set and cleared by software.
     + 0: IO port A clock disabled
     + 1: IO port A clock enabled

 * RCC_APB2ENR - SPI1
     - Bit 12 
     - SPI1EN: SPI1 clock enable
     - This bit is set and cleared by software.
     - 0: SPI1 clock disabled
     - 1: SPI1 clock enabled
*/


#define RCC_BASE        (0x40023800UL)

#define RCC_AHB1ENR_OFF (0x30UL)
#define RCC_APB2ENR_OFF (0x44UL)

/* TODO: move these macros to inline functions */
#define RCC_AHB1ENR_EN  do { REG32(RCC_BASE + RCC_AHB1ENR_OFF) |= (1U << 0); } while (0)
#define RCC_APB2ENR_EN  do { REG32(RCC_BASE + RCC_APB2ENR_OFF) |= (1U << 12); } while (0)


#endif      /* _GPIO_RCC */
