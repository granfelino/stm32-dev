#include "rcc_reg.h"

void rcc_enable() {
    rcc_ahb1_en();
    rcc_apb2_en();
}
