#ifndef _REG_UTIL_H
#define _REG_UTIL_H

#include <inttypes.h>

/* USAGE EXAMPLE: REG32(RCC_BASE + OFF) |= (1U << 12); */
#define REG32(x)    (*(volatile uint32_t *)(x))

#endif      /* _REG_UTIL_H */
