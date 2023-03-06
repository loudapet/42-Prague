/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:48:57 by plouda            #+#    #+#             */
/*   Updated: 2023/03/06 17:00:31 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_clstsize_flag(t_clist *lst)
{
	int	i;

	i = 0;
	if (lst->start == 1)
	{
		lst = lst->next;
	}
	while (lst->start != 1)
	{
		lst = lst->next;
		i++;
	}
	return (i + 1);
}

int	ft_clstsize(t_clist *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
