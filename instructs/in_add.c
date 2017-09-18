#include "../corewar.h"

int     in_add(t_bs *base, t_proc *pr)
{
    if (take_args(pr, base) == 0)
        return (0);
//    if (pr->args[0] != 1 || pr->args[1] != 1 || pr->args[2] != 1)
//        return (0);
    pr->pc = pr->pc + 2;
    if (!(is_reg(pr->regs[pr->pc + 2]) && is_reg(pr->regs[pr->pc + 1]) && is_reg(pr->regs[pr->pc])))
        return (0);
    pr->regs[pr->pc + 2] = pr->regs[pr->pc] + pr->regs[pr->pc + 1];
    //TODO carry change;
    return (1);

}