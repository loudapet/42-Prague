/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:46:16 by plouda            #+#    #+#             */
/*   Updated: 2023/02/24 10:44:33 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

t_clist	*ft_clstlast(t_clist *lst)
{
	int	i;

	i = ft_clstsize(lst);
	while (i > 1)
	{
		lst = lst->next;
		i--;
	}
	return (lst);
}

void	ft_clstadd_back(t_clist **lst, t_clist *new)
{
	t_clist	*last;

	if (!new)
		return ;
	last = ft_clstlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

t_clist	*ft_clstnew(int value)
{
	t_clist	*list;

	list = malloc(sizeof(t_clist));
	if (!list)
		return (NULL);
	list->value = value;
	list->next = NULL;
	return (list);
}
