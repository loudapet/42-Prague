/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cheapest_nbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:14:25 by plouda            #+#    #+#             */
/*   Updated: 2023/03/03 16:51:44 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_above_nbr(t_clist *stack_b, int value_a)
{
	int	curr_value;
	int	start_value;

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

t_values	get_values(t_clist *stack_a, t_clist *stack_b)
{
	t_values	values;

	values.value_a = stack_a->value;
	values.value_b = push_above_nbr(stack_b, values.value_a);
	return (values);
}

int	get_cheapest_nbr(t_clist *stack_a, t_clist *stack_b)
{
	t_values	values;
	int			candidate;
	int			cost;
	int			size;
	t_count		count;

	cost = -1;
	candidate = 0;
	size = ft_clstsize_flag(stack_a);
	while (size >= 1)
	{
		values = get_values(stack_a, stack_b);
		count = count_moves(stack_a, stack_b, values.value_a, values.value_b);
		//ft_printf("IMPORTANT: Cost of nbr %d: %d\n", values.value_a, get_cost(count));
		if (cost == -1 || get_cost(count) < cost)
		{
			cost = get_cost(count);
			candidate = values.value_a;
			ft_printf("CHANGE OF CANDIDATE: %d\n", candidate);
			ft_printf("Candidate flags: %c\n", count.flag_rev_rot_a_b);
			ft_printf("IMPORTANT: Cost of nbr %d: %d\n", values.value_a, get_cost(count));
		}

		stack_a = stack_a->next;
		size--;
	}
	ft_printf("Sent candidate: %d\n", candidate);
	return (candidate);
}
