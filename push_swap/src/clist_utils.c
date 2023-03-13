/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:46:16 by plouda            #+#    #+#             */
/*   Updated: 2023/03/13 15:15:07 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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

void	ft_clstadd_front(t_clist **lst, t_clist *new)
{
	if (!new)
		return ;
	if (!lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	new->prev = (*lst)->prev;
	new->start = 1;
	(*lst)->prev->next = new;
	(*lst)->prev = new;
	(*lst)->start = 0;
	*lst = new;
}

t_clist	*ft_clstnew(int value)
{
	t_clist	*list;

	list = malloc(sizeof(t_clist));
	if (!list)
		return (NULL);
	list->value = value;
	list->next = NULL;
	list->prev = NULL;
	list->start = 0;
	return (list);
}
