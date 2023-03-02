/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:14:25 by plouda            #+#    #+#             */
/*   Updated: 2023/03/02 23:49:07 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_above_nbr(t_clist *stack_b, int value_a)
{
	int	curr_value;
	int start_value;

	if (value_a > max_value(stack_b) || value_a < min_value(stack_b))
		return (max_value(stack_b));
	curr_value = value_a - 1;
	start_value = stack_b->value;
	while (curr_value > min_value(stack_b))
	{
		stack_b = stack_b->next;
		while (stack_b->start != 1)
		{
			if (curr_value == stack_b->value)
			{
				if (start_value > curr_value && start_value <= value_a)
					curr_value = start_value;
				return (curr_value);
			}
			stack_b = stack_b->next;
		}
		curr_value--;
	}
	if (start_value > curr_value && start_value <= value_a)
		curr_value = start_value;
	return (curr_value);
}

int	get_cost(t_count count)
{
	int	cost;

	cost = 0;
	if (count.flag_rev_rot_a_b == 'a')
		cost = count.rota_a + count.rev_rota_b;
	else if (count.flag_rev_rot_a_b == 'b')
		cost = count.rev_rota_a + count.rota_b;
	else if (count.flag_rev_rot_a_b == 'c')
		cost = count.rot;
	else if (count.flag_rev_rot_a_b == 'd')
		cost = count.rev_rot;
	return (cost);
}

int	get_cheapest_nbr(t_clist *stack_a, t_clist *stack_b)
{
	int	value_a;
	int	value_b;
	int	candidate;
	int	cost;
	t_count	count;

	cost = -1;
	candidate = 0;
	value_a = stack_a->value;
	value_b = push_above_nbr(stack_b, value_a);
	count = count_moves(stack_a, stack_b, value_a, value_b);
	if (cost == -1 || get_cost(count) < cost)
	{
			cost = get_cost(count);
			candidate = value_a;
	}
	stack_a = stack_a->next;
	while (stack_a->start != 1)
	{
		value_a = stack_a->value;
		value_b = push_above_nbr(stack_b, value_a);
		count = count_moves(stack_a, stack_b, value_a, value_b);
		if (cost == -1 || get_cost(count) < cost)
		{
			cost = get_cost(count);
			candidate = value_a;
		}
		stack_a = stack_a->next;
	}
	return (candidate);
}

