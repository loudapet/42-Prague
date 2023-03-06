/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:36:17 by plouda            #+#    #+#             */
/*   Updated: 2023/03/06 17:09:37 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 Swap the first 2 elements at the top of the stack.
Do nothing if there is only one or no elements.
*/
void	swap(t_clist *stack)
{
	int		value;

	if (!stack || ft_clstsize_flag(stack) == 1)
		return ;
	value = stack->value;
	stack->value = stack->next->value;
	stack->next->value = value;
}

void	swap_a(t_clist *stack_a)
{
	swap(stack_a);
	write(1, "sa\n", 3);
}

void	swap_b(t_clist *stack_b)
{
	swap(stack_b);
	write(1, "sb\n", 3);
}

void	swap_both(t_clist *stack_a, t_clist *stack_b)
{
	swap(stack_a);
	swap(stack_b);
	write(1, "ss\n", 3);
}
