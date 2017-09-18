#include "corewar.h"

char    *get_binary(unsigned int i, t_bs *base)
{
    printf("binary\n");
    char *ret;
    int a;
    int c;

    c = base->map[i+1];
    ret = ft_strnew(8);
    a = 7;
    while (a >= 0)
    {
        ret[a] = (c % 2) + 48;
        c /= 2;
        a--;
    }
    return (ret);
}
