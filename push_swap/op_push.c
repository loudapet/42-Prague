/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:55:54 by plouda            #+#    #+#             */
/*   Updated: 2023/03/13 12:48:24 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Removes a node from the top of the stack, redirects pointers and changes the
pointer to the head of the stack to the node following the removed one. If the
stack only contains one node, initializes a placeholder which can be later
filled with a proper node using f(ft_clst_addfront) from f(push).
*/
static int	pop(t_clist **stack)
{
	int		popped;
	t_clist	*del;

	del = *stack;
	if (ft_clstsize_flag(*stack) == 1)
	{
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

/*
Pushes a node to stack 'dest' using the value of the node removed from the
top of stack 'src'. If 'dest' is empty (= only contains the placeholder),
overwrites the placeholder node with actual values and redirects both
pointers to point at the new node, creating a self-enclosed doubly
circular linked list on which other clist functions can be executed.
*/
void	push(t_clist **src, t_clist **dest)
{
	int	value_to_push;

	if ((*src)->value == 0 && (*src)->next == NULL)
		return ;
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
