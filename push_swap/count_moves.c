/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:13:22 by plouda            #+#    #+#             */
/*   Updated: 2023/03/01 15:50:56 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_rota(t_clist *stack, int value)
{
	int	i;

	i = 1;
	if (stack->value == value)
		return (0);
	stack = stack->next;
	while (stack->value != value && stack->start != 1)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

int	count_rev_rota(t_clist *stack, int value)
{
	int	i;

	i = 1;
	if (stack->value == value)
		return (0);
	stack = stack->prev;
	while (stack->value != value && stack->start != 1)
	{
		i++;
		stack = stack->prev;
	}
	return (i);
}
