#include "corewar.h"

void	ft_usage()
{
	ft_printf("Usage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth]\
	[-a] <champion1.cor> <...>\n\
	-a        : Prints output from \"aff\" (Default is to hide it)\
	#### TEXT OUTPUT MODE ####################################################\
	#");

}

int 	main(int argc, char **argv)
{
	int 	fd;
	int		i;

	if (argc == 1)
		ft_usage();
	i = -1;
	while (++i < MAX_PLAYERS)
		;

	return 0;
}

// зчитування імені
/*

	unsigned int	arr[4];
	unsigned int	s;
	char			buf[4];
	int 			fd;
	int 			i;

	i = -1;
	fd = open(argv[1], O_RDONLY);
	read(fd, &buf, 4);

	*/
/*arr[0] = (unsigned int)(buf[0] << 24);
	arr[1] = (unsigned int)(buf[1] << 16 & 0x00ffffff);
	arr[2] = (unsigned int)(buf[2] << 8 & 0x0000ffff);
	arr[3] = (unsigned int)(buf[3] & 0x000000ff);
	s = arr[0] | arr[1] | arr[2] | arr[3];*//*


while (++i < 4)
ft_printf("s = %X\n", buf[i]);
ft_printf("sum = %u\n", s);
return 0;

*/
