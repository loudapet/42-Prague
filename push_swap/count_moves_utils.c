/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_moves_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:50:46 by plouda            #+#    #+#             */
/*   Updated: 2023/03/02 21:13:37 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_count	init_count(int rota_a, int rota_b, int rev_rota_a, int rev_rota_b)
{
	t_count	count;

	count.rota_a = rota_a;
	count.rota_b = rota_b;
	count.rev_rota_a = rev_rota_a;
	count.rev_rota_b = rev_rota_b;
	count.rot = 0;
	count.rev_rot = 0;
	count.diff_a_b = 0;
	count.diff_b_a = 0;
	count.fin_rot = 0;
	count.fin_diff = 0;
	count.flag_rot_diff = 'x';
	count.flag_rev_rot_a_b = 'x';
	return (count);
}

int	max_value(t_clist *stack)
{
	int	max;

	max = stack->value;
	stack = stack->next;
	while (stack->start != 1)
	{
		if (stack->value > max)
			max = stack->value;
		stack = stack->next;
	}
	return (max);
}

int	min_value(t_clist *stack)
{
	int	min;

	min = stack->value;
	stack = stack->next;
	while (stack->start != 1)
	{
		if (stack->value < min)
			min = stack->value;
		stack = stack->next;
	}
	return (min);
}

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
