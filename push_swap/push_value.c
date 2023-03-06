/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:55:48 by plouda            #+#    #+#             */
/*   Updated: 2023/03/06 17:15:37 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_moves(t_clist *stack_a, t_clist *stack_b, t_count count)
{
	if (count.flag_rev_rot_a_b == 'a')
		flag_a(stack_a, stack_b, count);
	if (count.flag_rev_rot_a_b == 'b')
		flag_b(stack_a, stack_b, count);
	if (count.flag_rev_rot_a_b == 'c')
		flag_c(stack_a, stack_b, count);
	if (count.flag_rev_rot_a_b == 'd')
		flag_d(stack_a, stack_b, count);
}

void	push_value(t_clist **stack_a, t_clist **stack_b)
{
	int			size;
	t_count		count;
	t_values	values;

	values.value_a = 0;
	size = ft_clstsize_flag(*stack_a);
	while (size > 3)
	{
		values.value_a = get_cheapest_nbr(*stack_a, *stack_b);
		values.value_b = push_above_nbr(*stack_b, values.value_a);
		while ((*stack_a)->value != values.value_a)
			*stack_a = (*stack_a)->next;
		count = count_moves(*stack_a, *stack_b, values.value_a, values.value_b);
		while ((*stack_a)->start != 1)
			*stack_a = (*stack_a)->next;
		do_moves(*stack_a, *stack_b, count);
		while ((*stack_a)->start != 1)
			*stack_a = (*stack_a)->next;
		push_b(stack_a, stack_b);
		size--;
	}
}
