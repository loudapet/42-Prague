/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:46:16 by plouda            #+#    #+#             */
/*   Updated: 2023/02/27 15:38:10 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
void	ft_cprev_set(t_clist *lst)
{
	if (lst->start == 1)
	{
		lst = lst->next;
	}
	while (lst->start != 1)
	{
		lst->next->prev = lst;
		lst = lst->next;
	}
	lst->next->prev = lst;
}
*/

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

t_clist	*ft_clstlast_flag(t_clist *lst)
{
	int	i;

	i = ft_clstsize_flag(lst);
	while (i > 1)
	{
		lst = lst->next;
		i--;
	}
	return (lst);
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
	if ((*lst)->next == NULL)
	{
		(*lst)->next = *lst;
		(*lst)->prev = *lst;
		(*lst)->start = 1;
		(*lst)->value = new->value;
		return ;
	}
	(*lst)->prev->next = new;
	(*lst)->prev = new;
	(*lst)->start = 0;
	new->next = *lst;
	new->prev = (*lst)->prev;
	new->start = 1;
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
