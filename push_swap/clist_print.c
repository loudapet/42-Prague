/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:26:18 by plouda            #+#    #+#             */
/*   Updated: 2023/03/07 12:52:43 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Purely testing functions used in troubleshooting. Both functions
display the stacks on the output. More precisely, they display each
node, followed by its value as well as its start flag. Under normal
circumstances, only the top node should have start set to 1.
*/
void	print_clist_a(t_clist *stack)
{
	int	i;

	i = 1;
	ft_printf("\n-------------STACK A-------------\n");
	if (stack->next == NULL)
	{
		ft_printf("%s", "              EMPTY\n");
		ft_printf("---------------------------------\n");
		return ;
	}
	ft_printf("(node%d.value:  %i, ", i, stack->value);
	ft_printf("node%d.start: %i)\n", i++, stack->start);
	stack = stack->next;
	while (stack->start != 1)
	{
		ft_printf("(node%d.value:  %i, ", i, stack->value);
		ft_printf("node%d.start: %i)\n", i++, stack->start);
		stack = stack->next;
	}
	ft_printf("---------------------------------\n");
}

void	print_clist_b(t_clist *stack)
{
	int	i;

	i = 1;
	ft_printf("\n-------------STACK B-------------\n");
	if (stack->next == NULL)
	{
		ft_printf("%s", "              EMPTY\n");
		ft_printf("---------------------------------\n");
		return ;
	}
	ft_printf("(node%d.value:  %i, ", i, stack->value);
	ft_printf("node%d.start: %i)\n", i++, stack->start);
	stack = stack->next;
	while (stack->start != 1)
	{
		ft_printf("(node%d.value:  %i, ", i, stack->value);
		ft_printf("node%d.start: %i)\n", i++, stack->start);
		stack = stack->next;
	}
	ft_printf("---------------------------------\n");
}
