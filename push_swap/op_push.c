/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:55:54 by plouda            #+#    #+#             */
/*   Updated: 2023/02/28 15:58:30 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	pop(t_clist **stack)
{
	int	popped;
	t_clist	*del;

	del = *stack;
	if (ft_clstsize_flag(*stack) == 1)
	{
		// placeholder solution
		popped = (*stack)->value;
		(*stack)->next = NULL;
		(*stack)->prev = NULL;
		(*stack)->start = 0;
		(*stack)->value = 0;
		return (popped);
	}
	popped = (*stack)->value;
	(*stack)->prev->next = (*stack)->next;
	(*stack)->next->prev = (*stack)->prev;
	(*stack) = (*stack)->next;
	(*stack)->start = 1;
	free(del);
	return (popped);
}


void	push(t_clist **src, t_clist **dest)
{
	int	value_to_push;
	
	value_to_push = pop(src);
	if ((*dest)->next == NULL)
	{
		(*dest)->next = *dest;
		(*dest)->prev = *dest;
		(*dest)->start = 1;
		(*dest)->value = value_to_push;
		return ;
	}
	else
		ft_clstadd_front(dest, ft_clstnew(value_to_push));
}

void	push_a(t_clist **stack_a, t_clist **stack_b)
{
	push(stack_b, stack_a);
	write(1, "pa\n", 3);
}

void	push_b(t_clist **stack_a, t_clist **stack_b)
{
	push(stack_a, stack_b);
	write(1, "pb\n", 3);
}
