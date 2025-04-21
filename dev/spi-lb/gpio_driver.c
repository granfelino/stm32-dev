#include <inttypes.h>
#include "gpio_reg.h"


void gpio_setup() {
    gpio_a_mode_set();
    gpio_a_speed_set();
    gpio_a_pupd_set();
    gpio_a_af_set();
}
