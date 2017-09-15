#include "corewar.h"


void	print_memory(const void *addr, size_t size)
{
    size_t i;
    size_t a;
    unsigned char const *ptr = addr;
    char const *base = "0123456789abcdef";

    i = 0;
    while (i < size)
    {
        a = 0;
        while (a < 64 && a + i < size)
        {
            write(1, base + (*(ptr + i + a) / 16)%16, 1);
            write(1, base + (*(ptr + i + a) % 16), 1);
            if (a % 2)
                write(1, " ", 1);
            a++;
        }
        while (a < 64)
        {
            write(1, "  ", 2);
            if (a % 2)
                write(1, " ", 1);
            a++;
        }
        a = 0;
        write(1, "\n", 1);
        i += 64;
    }
}

void     print_map(t_bs base) {
    print_memory(base.map, MEM_SIZE);
}