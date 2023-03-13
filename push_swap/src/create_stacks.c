/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stacks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:37:58 by plouda            #+#    #+#             */
/*   Updated: 2023/03/13 15:15:19 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
Initializes stack a by first creating a circular linked list
and then connecting the empty prev pointers to create
a doubly circular linked list
*/
t_clist	*create_stack_a(int argc, const char **argv, int flag)
{
	t_clist	*stack_a;
	int		value;
	int		i;

	i = flag;
	value = ft_atoi(argv[i++]);
	stack_a = ft_clstnew(value);
	stack_a->start = 1;
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		ft_clstadd_back(&stack_a, ft_clstnew(value));
		i++;
	}
	ft_clstlast(stack_a)->next = stack_a;
	while (stack_a->next->prev == NULL)
	{
		stack_a->next->prev = stack_a;
		stack_a = stack_a->next;
	}
	return (stack_a);
}

/*
Initializes stack b by creating a dummy node that
gets overwritten during the first push from a to b
*/
t_clist	*create_stack_b(void)
{
	t_clist	*stack_b;

	stack_b = ft_clstnew(0);
	stack_b->start = 0;
	return (stack_b);
}
