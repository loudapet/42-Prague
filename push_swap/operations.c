/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:43:31 by plouda            #+#    #+#             */
/*   Updated: 2023/02/28 11:18:05 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_a(t_clist *stack_a)
{
	//t_clist	*tmp;
	int		value;

	if (!stack_a || ft_clstsize_flag(stack_a) == 1)
		return;
	//tmp = stack_a;
	value = stack_a->value;
	stack_a->value = stack_a->next->value;
	stack_a->next->value = value;
	//stack_a = tmp;
}

void	rotate_a(t_clist *stack_a)
{
	//t_clist *tmp;
	int		value;

	if (!stack_a || ft_clstsize_flag(stack_a) == 1)
		return;
	while (stack_a->next->start != 1)
	{
		//tmp = stack_a;
		value = stack_a->value;
		stack_a->value = stack_a->next->value;
		stack_a->next->value = value;
		//stack_a = tmp;
		stack_a = stack_a->next;
	}
}

void	reverse_rotate_a(t_clist *stack_a)
{
	//t_clist *tmp;
	int		value;

	if (!stack_a || ft_clstsize_flag(stack_a) == 1)
		return;
	while (stack_a->prev->start != 1)
	{
		//tmp = stack_a;
		value = stack_a->value;
		stack_a->value = stack_a->prev->value;
		stack_a->prev->value = value;
		//stack_a = tmp;
		stack_a = stack_a->prev;
	}
}


int	pop_a(t_clist **stack_a)
{
	int	popped;
	t_clist	*del;

	del = *stack_a;
	if (ft_clstsize_flag(*stack_a) == 1)
	{
		// placeholder solution
		popped = (*stack_a)->value;
		(*stack_a)->next = NULL;
		(*stack_a)->prev = NULL;
		(*stack_a)->start = 0;
		(*stack_a)->value = 0;
		return (popped);
	}
	popped = (*stack_a)->value;
	(*stack_a)->prev->next = (*stack_a)->next;
	(*stack_a)->next->prev = (*stack_a)->prev;
	(*stack_a) = (*stack_a)->next;
	(*stack_a)->start = 1;
	free(del);
	return (popped);
}


void	push_b(t_clist **stack_a, t_clist **stack_b)
{
	int	value_to_push;
	
	value_to_push = pop_a(stack_a);
	if ((*stack_b)->next == NULL)
	{
		(*stack_b)->next = *stack_b;
		(*stack_b)->prev = *stack_b;
		(*stack_b)->start = 1;
		(*stack_b)->value = value_to_push;
		return ;
	}
	else
		ft_clstadd_front(stack_b, ft_clstnew(value_to_push));
}
