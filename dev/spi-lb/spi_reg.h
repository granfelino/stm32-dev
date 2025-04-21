#ifndef _SPI_REG_H
#define _SPI_REG_H

#include <inttypes.h>
#include <reg_util.h>


#define SPI1_BASE       (0x40013000UL)

#define SPI_CR1_CPHA       (0x1 << 0)
#define SPI_CR1_CPOL       (0x1 << 1)
#define SPI_CR1_MSTR       (0x1 << 2)
#define SPI_CR1_BR         (0b010 << 3)
#define SPI_CR1_LSBFIRST   (0x0 << 7)
#define SPI_CR1_SSI        (0x1 << 8)
#define SPI_CR1_SSM        (0x1 << 9)
#define SPI_CR1_RXONLY     (0x0 << 10)
#define SPI_CR1_DFF        (0x1 << 11)
#define SPI_CR1_BIDIMODE   (0x1 << 15)


struct spi {
    volatile uint32_t SPI_CR1;
    volatile uint32_t SPI_CR2;
    volatile uint32_t SPI_SR;
    volatile uint32_t SPI_DR;
};

#define SPI1        ((volatile struct spi *)(SPI1_BASE))

static inline void spi1_cr1_config() {
    SPI1->SPI_CR1 = 0x0000;
    SPI1->SPI_CR1 |= SPI_CR1_CPOL     |
                     SPI_CR1_CPHA     |
                     SPI_CR1_MSTR     |
                     SPI_CR1_BR       |
                     SPI_CR1_LSBFIRST |
                     SPI_CR1_SSI      |
                     SPI_CR1_SSM      |
                     SPI_CR1_RXONLY   |
                     SPI_CR1_DFF      |
                     SPI_CR1_BIDIMODE;
}

void spi1_config();
void spi1_enable();
void spi1_disable();


#endif      /* _SPI_REG_H */
