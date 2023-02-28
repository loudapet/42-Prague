/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:54:58 by plouda            #+#    #+#             */
/*   Updated: 2023/02/28 15:59:01 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_clist *stack)
{
	int		value;

	if (!stack || ft_clstsize_flag(stack) == 1)
		return;
	while (stack->next->start != 1)
	{
		value = stack->value;
		stack->value = stack->next->value;
		stack->next->value = value;
		stack = stack->next;
	}
}

void	rotate_a(t_clist *stack_a)
{
	rotate(stack_a);
	write(1, "ra\n", 3);
}

void	rotate_b(t_clist *stack_b)
{
	rotate(stack_b);
	write(1, "rb\n", 3);
}

void	rotate_both(t_clist *stack_a, t_clist *stack_b)
{
	rotate(stack_a);
	rotate(stack_b);
	write(1, "rr\n", 3);
}
