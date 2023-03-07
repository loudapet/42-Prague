/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cheapest_nbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 21:14:25 by plouda            #+#    #+#             */
/*   Updated: 2023/03/07 12:14:34 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Computes how many moves it takes for a number to get pushed
to the correct position
*/
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

/*
Computes what value from stack a is being pushed
above what number in stack b
*/
t_values	get_values(t_clist *stack_a, t_clist *stack_b)
{
	t_values	values;

	values.value_a = stack_a->value;
	values.value_b = push_above_nbr(stack_b, values.value_a);
	return (values);
}

/*
Computes what number from stack a is the cheapest to push
to stack b. The function counts moves for every value in
stack_a and chooses the value with the lowest cost to save
as a candidate, which in turn gets passed to push_value.
*/
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
		if (cost == -1 || get_cost(count) < cost)
		{
			cost = get_cost(count);
			candidate = values.value_a;
		}
		stack_a = stack_a->next;
		size--;
	}
	return (candidate);
}
