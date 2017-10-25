/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_base_to_zero_error.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddovzhik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 00:02:19 by ddovzhik          #+#    #+#             */
/*   Updated: 2017/10/24 00:02:20 by ddovzhik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../corewar.h"

void	del_list_champ(t_chmp **champ)
{
	t_chmp *tmp;
	t_chmp *trash;

	trash = *champ;
	while (trash)
	{
		tmp = trash->next;
		free(trash->instructions);
		free(trash);
		trash = tmp;
	}
	*champ = NULL;
}

void	del_list_proc(t_proc **proc)
{
	t_proc *tmp;
	t_proc *trash;

	trash = *proc;
	while (trash)
	{
		tmp = trash->next;
		free(trash);
		trash = tmp;
	}
	*proc = NULL;
}

void	base_to_zero(t_bs *bs)
{
	int i;

	bs->list_champs = NULL;
	bs->list_proc = NULL;
	i = -1;
	while (++i < MEM_SIZE)
	{
		bs->map[i] = 0;
		bs->color_map[i].champ = 0;
		bs->color_map[i].live = 0;
	}
	bs->np = 0;
	bs->num_live = 0;
	bs->is_dump = 0;
	bs->is_print = 0;
	bs->is_visual = 0;
	bs->is_num_flag = 0;
	bs->is_aff = 0;
	bs->is_beep = 0;
	g_count = 0;
}

/*
**	i flags for error
**	1 - usage;
** 	2 - error in max players;
**	3 - error for magic;
**	4 - error when size of code is 0;
**	5 - error in malloc;
**	6 - number of player is doesnt digit
**	7 - number of cycles is doesnt digit
**  8 - number is not unsigned int
**	9 - number of print cicles must be a digit
**	10
**	11 - number of player must be a 1 <= number < MAX_PLAYERS
**	12 - identical numbers
*/

void	ft_error1(int i, char *str)
{
	if (i == 8)
		ft_printf(RED"Error:"BLU"\n\t\t%s"RC" is not unsigned int\n", str);
	else if (i == 9)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-print N]"RC" - must be a digit\n");
	else if (i == 10)
		ft_printf(RED"Error:"BLU"\n\t\tnot enough arguments"RC"\n", str);
	else if (i == 11)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-n number]"RC" - should be in the "\
		"range 1 <= number <= MAX_PLAYER\n");
	else if (i == 12)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-n number]"RC" - identical numbers"\
		"\n");
	else if (i == 13)
		ft_printf(RED"Error:"RC"\n\t\tchamps - should be in the range 1 <= num"\
		"ber <= MAX_PLAYER\n");
	else if (i == 14)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-dump N]"RC" - must be a digit"\
		"\n");
	else if (i == 15)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-print N]"RC" - must be a digit"\
		"\n");
	del_list_proc(&g_p_base->list_proc);
	del_list_champ(&g_p_base->list_champs);
	exit(1);
}

void	ft_error(int i, char *str)
{
	i == 2 ? perror("error") : 0;
	if (i == 1)
		ft_printf(RED"Usage:"RC"\n\t./corewar [[-dump N] [-print N] [-a] [-b]]"\
		" | [[-n number] champion1.cor] | -v] \n\tMax players is %d\n\n#### T"\
		"EXT OUTPUT MODE #####################################################"\
		"#####\n\t-dump N\t\t: Dumps memory after N cycles then exits;\n\t-pri"\
		"nt N\t: Every N cycles, print dump memory;\n\t-a\t\t\t: Prints output"\
		" from \"aff\" (Default is to hide it);\n\t-b\t\t\t: Enable sound when"\
		" process is die;\n\t-n number\t: Sets the number of the next player\n"\
		"\n#### NCURSES OUTPUT MODE ##########################################"\
		"#############\n\t-v\t\t\t: Ncurses output mode\n", MAX_PLAYERS);
	else if (i == 3)
		ft_printf(RED"Error:"RC"\n\t\tFile "BLU"%s"RC" has an invalid magic na"\
		"me\n", str);
	else if (i == 4)
		ft_printf(RED"Error:"RC"\n\t\tFile "BLU"%s"RC" has a code size that di"\
		"ffer from what its header says\n", str);
	else if (i == 5)
		ft_printf(RED"Error:"RC"\n\t\tin malloc\n");
	else if (i == 6)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-n number]"RC" - must be a digit"\
		"\n");
	else if (i == 7)
		ft_printf(RED"Error:"RC"\n\t\t"BLU"[-dump N]"RC" - must be a digit\n");
	ft_error1(i, str);
}
