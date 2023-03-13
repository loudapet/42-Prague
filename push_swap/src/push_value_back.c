/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_value_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:25:57 by plouda            #+#    #+#             */
/*   Updated: 2023/03/13 15:15:50 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
Figures out above what number in stack a the value from stack b
should be pushed.
The rules are as follows:
If value_b > max_value OR value_b < min_value in stack_b, push value_b
above min_value in stack a.
If max_value(stack_a) > value_b > min_value(stack_a), find the closest
number to value_b in stack a that is larger than value_b, and push value_b
above said number.
*/
int	push_above_nbr_a(t_clist *stack_a, int value_b)
{
	int	curr_value;
	int	start_value;

	if (value_b > max_value(stack_a) || value_b < min_value(stack_a))
		return (min_value(stack_a));
	curr_value = value_b + 1;
	start_value = stack_a->value;
	while (curr_value < max_value(stack_a))
	{
		stack_a = stack_a->next;
		while (stack_a->start != 1)
		{
			if (curr_value == stack_a->value)
			{
				if (start_value < curr_value && start_value >= value_b)
					curr_value = start_value;
				return (curr_value);
			}
			stack_a = stack_a->next;
		}
		curr_value++;
	}
	if (start_value < curr_value && start_value >= value_b)
		curr_value = start_value;
	return (curr_value);
}

/*
Decides what moves are applicable depending on which is cheaper.
Unlike for do_moves in push_value, it does not handle rotations
which are done on both stacks at the same time, as the number
which is being pushed from stack b is always the top number, and
only stack a must rotate.
 */
static void	do_moves(t_clist *stack, t_count count)
{
	if (count.rota_b > count.rev_rota_b)
	{
		while (count.rev_rota_b > 0)
		{
			reverse_rotate_a(stack);
			count.rev_rota_b--;
		}
	}
	else
	{
		while (count.rota_b > 0)
		{
			rotate_a(stack);
			count.rota_b--;
		}
	}
}

/*
Pushes the cheapest number from stack a to the correct position
in stack b. As multiple functions called from push_value rely on
iterations of stack_b, it also handles resetting the position of
the head of the stack everytime it is required.
As opposed to push_value, the arguments passed to functions called
from push_value_back are reversed, i.e. value_a becomes value_b,
stack a becomes stack b for the purposes of said functions.
*/
void	push_value_back(t_clist **stack_a, t_clist **stack_b)
{
	int			size;
	t_count		count;
	t_values	values;

	size = ft_clstsize_flag(*stack_b);
	while (size > 0)
	{
		values.value_b = (*stack_b)->value;
		values.value_a = push_above_nbr_a(*stack_a, values.value_b);
		count = count_moves(*stack_b, *stack_a, values.value_b, values.value_a);
		while ((*stack_b)->start != 1)
			*stack_a = (*stack_b)->next;
		do_moves(*stack_a, count);
		while ((*stack_b)->start != 1)
			*stack_b = (*stack_b)->next;
		push_a(stack_a, stack_b);
		size--;
	}
}
