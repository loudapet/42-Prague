/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:55:48 by plouda            #+#    #+#             */
/*   Updated: 2023/03/03 16:49:47 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	flag_d(t_clist *stack_a, t_clist *stack_b, t_count count)
{
	while (count.rev_rota_a > 0 && count.rev_rota_b > 0)
	{
		reverse_rotate_both(stack_a, stack_b);
		count.rev_rota_a--;
		count.rev_rota_b--;
	}
	while (count.rev_rota_a > 0)
	{
		reverse_rotate_a(stack_a);
		count.rev_rota_a--;
	}
	while (count.rev_rota_b > 0)
	{
		reverse_rotate_b(stack_b);
		count.rev_rota_b--;
	}
}

static void	flag_c(t_clist *stack_a, t_clist *stack_b, t_count count)
{
	while (count.rota_a > 0 && count.rota_b > 0)
	{
		rotate_both(stack_a, stack_b);
		count.rota_a--;
		count.rota_b--;
	}
	while (count.rota_a > 0)
	{
		rotate_a(stack_a);
		count.rota_a--;
	}
	while (count.rota_b > 0)
	{
		rotate_b(stack_b);
		count.rota_b--;
	}
}

static void	flag_b(t_clist *stack_a, t_clist *stack_b, t_count count)
{
	while (count.rota_b > 0)
	{
		rotate_b(stack_b);
		count.rota_b--;
	}
	while (count.rev_rota_a > 0)
	{
		reverse_rotate_a(stack_a);
		count.rev_rota_a--;
	}
}

static void	flag_a(t_clist *stack_a, t_clist *stack_b, t_count count)
{
	while (count.rota_a > 0)
	{
		rotate_a(stack_a);
		count.rota_a--;
	}
	while (count.rev_rota_b > 0)
	{
		reverse_rotate_b(stack_b);
		count.rev_rota_b--;
	}
}

void	do_moves(t_clist *stack_a, t_clist *stack_b, t_count count)
{
	if (count.flag_rev_rot_a_b == 'a')
		flag_a(stack_a, stack_b, count);
	if (count.flag_rev_rot_a_b == 'b')
		flag_b(stack_a, stack_b, count);
	if (count.flag_rev_rot_a_b == 'c')
		flag_c(stack_a, stack_b, count);
	if (count.flag_rev_rot_a_b == 'd')
		flag_d(stack_a, stack_b, count);
}

void	push_value(t_clist **stack_a, t_clist **stack_b)
{
	int	size;
	t_count	count;
	t_values values;

	values.value_a = 0;
	size = ft_clstsize_flag(*stack_a);
	print_clist_a(*stack_a);
	print_clist_b(*stack_b);
	
	while (size > 3)
	{
		values.value_a = get_cheapest_nbr(*stack_a, *stack_b);
		ft_printf("CHEAPEST NUMBER: %d\n", values.value_a);
		values.value_b = push_above_nbr(*stack_b, values.value_a);
		ft_printf("Value on stack a: %d\n", (*stack_a)->value);
		while ((*stack_a)->value != values.value_a)
			*stack_a = (*stack_a)->next;
		count = count_moves(*stack_a, *stack_b, values.value_a, values.value_b);
		ft_printf("Flags of %d before moves: %c\n", values.value_a, count.flag_rev_rot_a_b);
		while ((*stack_a)->start != 1)
			*stack_a = (*stack_a)->next;
		do_moves(*stack_a, *stack_b, count);
		//ft_printf("Flags of %d: %c\n", values.value_a, count.flag_rev_rot_a_b);
		//print_clist_a(*stack_a);
		//print_clist_b(*stack_b);
		while ((*stack_a)->start != 1)
			*stack_a = (*stack_a)->next;
		push_b(stack_a, stack_b);
		print_clist_a(*stack_a);
		print_clist_b(*stack_b);
		ft_printf("Size: %d\n", size);
		size--;
	}
	print_clist_a(*stack_a);
	print_clist_b(*stack_b);
}
