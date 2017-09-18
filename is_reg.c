#include "corewar.h"

int     is_reg(unsigned int reg){
    if (reg > 0 && reg <= REG_NUMBER)
        return (1);
    return 0;
}
