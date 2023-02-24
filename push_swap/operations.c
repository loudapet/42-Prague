/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:43:31 by plouda            #+#    #+#             */
/*   Updated: 2023/02/24 15:17:20 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_a(t_clist *lst)
{
	t_clist	*tmp;
	int		value;

	if (!lst || ft_clstsize_flag(lst) == 1)
		return;
	tmp = lst;
	value = lst->value;
	lst->value = lst->next->value;
	lst->next->value = value;
	lst = tmp;
}

void	rotate_a(t_clist *lst)
{
	t_clist *tmp;
	int		value;

	if (!lst || ft_clstsize_flag(lst) == 1)
		return;
	while (lst->next->start != 1)
	{
		tmp = lst;
		value = lst->value;
		lst->value = lst->prev->value;
		lst->prev->value = value;
		lst = tmp;
		lst = lst->next;
	}
}

void	reverse_rotate_a(t_clist *lst)
{
	t_clist *tmp;
	int		value;

	if (!lst || ft_clstsize_flag(lst) == 1)
		return;
	while (lst->prev->start != 1)
	{
		tmp = lst;
		value = lst->value;
		lst->value = lst->prev->value;
		lst->prev->value = value;
		lst = tmp;
		lst = lst->prev;
	}
}