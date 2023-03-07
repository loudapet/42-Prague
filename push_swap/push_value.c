/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:55:48 by plouda            #+#    #+#             */
/*   Updated: 2023/03/07 12:22:58 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Figures out above what number in stack b the value from stack a
should be pushed.
The rules are as follows:
If value_a > max_value OR value_a < min_value in stack_b, push value_a
above max_value in stack b.
If max_value(stack_b) > value_a > min_value(stack_b), find the closest
number to value_a in stack b that is smaller than value_a, and push value_a
above said number.
*/
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

/* Decides what moves are applicable depending on the flag from t_count */
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

/*
Pushes the cheapest number from stack a to the correct position
in stack b. As multiple functions called from push_value rely on
iterations of stack_a, it also handles resetting the position of
the head of the stack everytime it is required.
*/
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
