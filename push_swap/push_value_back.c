/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_value_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 22:25:57 by plouda            #+#    #+#             */
/*   Updated: 2023/03/06 17:15:14 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	push_above_nbr_a(t_clist *stack_a, int value_b)
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

static void	move_up(t_clist *stack_a, int rot, int rev_rot)
{
	if (rot > rev_rot)
	{
		while (rev_rot > 0)
		{
			reverse_rotate_a(stack_a);
			rev_rot--;
		}
	}
	else
	{
		while (rot > 0)
		{
			rotate_a(stack_a);
			rot--;
		}
	}
}

void	rotate_lowest_up(t_clist **stack_a)
{
	int	rot;
	int	rev_rot;

	while ((*stack_a)->value != min_value(*stack_a))
		*stack_a = (*stack_a)->next;
	rot = count_rota_a(*stack_a);
	rev_rot = count_rev_rota_a(*stack_a);
	while ((*stack_a)->start != 1)
		*stack_a = (*stack_a)->next;
	move_up(*stack_a, rot, rev_rot);
}
