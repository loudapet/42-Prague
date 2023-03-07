/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_moves_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:50:46 by plouda            #+#    #+#             */
/*   Updated: 2023/03/07 12:33:24 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
rot:			larger value out of rota_a, rota_b
rev_rot:		larger value out of rev_rota_a, rev_rota_b
diff_a_b:		sum of rota_a + rev_rota_b
diff_b_a:		sum of rota_b + rev_rota_a
fin_rot:		smaller value out of rot, rev_rot
fin_diff:		smaller value out of diff_a_b, diff_b_a
flag_rot_diff:	decides if the preference is to rotate both stacks at once
				or if it is cheaper to rotate them separately, which in turn
				decides what flags from flag_a_b will be used
	options:	's':	rotate stacks separately
				't':	rotate stacks together
flag_a_b:		flag_rot_diff 's':
				decides whether to rotate stack a and rev_rotate
				stack b or vice versa
					'a': rotate stack a, reverse rotate stack b
					'b': rotate stack b, reverse rotate stack a
				flag_rot_diff 't':
				decides if the preference is to rotate 
				or rev_rotate both stacks
					'c': rotate both stacks
					'd': reverse rotate both stacks
*/
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

/* Computes the maximum value of the stack */
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

/* Computes the minimum value of the stack */
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
