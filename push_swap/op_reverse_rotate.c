/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_reverse_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:55:33 by plouda            #+#    #+#             */
/*   Updated: 2023/03/06 17:09:18 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Shift all elements of the stack down by 1.
The last element becomes the first one.
*/
void	reverse_rotate(t_clist *stack)
{
	int		value;

	if (!stack || ft_clstsize_flag(stack) == 1)
		return ;
	while (stack->prev->start != 1)
	{
		value = stack->value;
		stack->value = stack->prev->value;
		stack->prev->value = value;
		stack = stack->prev;
	}
}

void	reverse_rotate_a(t_clist *stack_a)
{
	reverse_rotate(stack_a);
	write(1, "rra\n", 4);
}

void	reverse_rotate_b(t_clist *stack_b)
{
	reverse_rotate(stack_b);
	write(1, "rrb\n", 4);
}

void	reverse_rotate_both(t_clist *stack_a, t_clist *stack_b)
{
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	write(1, "rrr\n", 4);
}
