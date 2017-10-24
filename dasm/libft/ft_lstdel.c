/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 13:29:36 by ysalata           #+#    #+#             */
/*   Updated: 2016/12/05 14:43:14 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void			ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *buf;
	t_list *list;

	if (alst == NULL)
		return ;
	list = *alst;
	while (list != NULL)
	{
		buf = list->next;
		ft_lstdelone(&list, del);
		list = buf;
	}
	*alst = NULL;
}
