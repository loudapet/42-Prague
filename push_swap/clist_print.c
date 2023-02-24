/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:26:18 by plouda            #+#    #+#             */
/*   Updated: 2023/02/24 12:47:16 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_clist(t_clist *stack)
{
	int	i;

	i = 1;
	ft_printf("____________CLOCKWISE___________\n");
	ft_printf("(node%d.value:  %i, ", i, stack->value);
	ft_printf("node%d.start: %i)\n", i++, stack->start);
	stack = stack->next;
	while (stack->start != 1)
	{
		ft_printf("(node%d.value:  %i, ", i, stack->value);
		ft_printf("node%d.start: %i)\n", i++, stack->start);
		stack = stack->next;
	}
	write(1, "\n", 1);
}

void	print_clist_rev(t_clist *stack)
{
	int	i;

	i = 1;
	ft_printf("________COUNTER-CLOCKWISE_______\n");
	ft_printf("(node%d.value:  %i, ", i, stack->value);
	ft_printf("node%d.start: %i)\n", i++, stack->start);
	stack = stack->prev;
	while (stack->start != 1)
	{
		ft_printf("(node%d.value:  %i, ", i, stack->value);
		ft_printf("node%d.start: %i)\n", i++, stack->start);
		stack = stack->prev;
	}
}
