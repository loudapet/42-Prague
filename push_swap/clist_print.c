/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clist_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:26:18 by plouda            #+#    #+#             */
/*   Updated: 2023/02/27 14:58:54 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_clist(t_clist *stack)
{
	int	i;

	i = 1;
	ft_printf("__________FRONT-TO-BACK__________\n");
	if (stack->next == NULL)
	{
		ft_printf("%s", "EMPTY\n");
		return;
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
	write(1, "\n", 1);
}

void	print_clist_swap(t_clist *stack)
{
	int	i;

	i = 1;
	ft_printf("_____________SWAPPED____________\n");
	if (stack->next == NULL)
	{
		ft_printf("%s", "EMPTY\n");
		return;
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
	write(1, "\n", 1);
}

void	print_clist_rev(t_clist *stack)
{
	int	i;

	i = 1;
	ft_printf("__________BACK-TO-FRONT_________\n");
	if (stack->next == NULL)
	{
		ft_printf("%s", "EMPTY\n");
		return;
	}
	ft_printf("(node%d.value:  %i, ", i, stack->value);
	ft_printf("node%d.start: %i)\n", i++, stack->start);
	stack = stack->prev;
	while (stack->start != 1)
	{
		ft_printf("(node%d.value:  %i, ", i, stack->value);
		ft_printf("node%d.start: %i)\n", i++, stack->start);
		stack = stack->prev;
	}
	write(1, "\n", 1);
}

void	print_clist_rev_swap(t_clist *stack)
{
	int	i;

	i = 1;

	ft_printf("___________REV-SWAPPED__________\n");
	if (stack->next == NULL)
	{
		ft_printf("%s", "EMPTY\n");
		return;
	}
	ft_printf("(node%d.value:  %i, ", i, stack->value);
	ft_printf("node%d.start: %i)\n", i++, stack->start);
	stack = stack->prev;
	while (stack->start != 1)
	{
		ft_printf("(node%d.value:  %i, ", i, stack->value);
		ft_printf("node%d.start: %i)\n", i++, stack->start);
		stack = stack->prev;
	}
	write(1, "\n", 1);

}

void	print_clist_rotated(t_clist *stack)
{
	int	i;

	i = 1;

	ft_printf("_____________ROTATED____________\n");
	if (stack->next == NULL)
	{
		ft_printf("%s", "EMPTY\n");
		return;
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
	write(1, "\n", 1);
}

void	print_clist_rev_rotated(t_clist *stack)
{
	int	i;

	i = 1;

	ft_printf("___________REV-ROTATED__________\n");
	if (stack->next == NULL)
	{
		ft_printf("%s", "EMPTY\n");
		return;
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
	write(1, "\n", 1);
}
