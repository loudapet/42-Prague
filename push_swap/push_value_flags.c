/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_value_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:54:38 by plouda            #+#    #+#             */
/*   Updated: 2023/03/06 16:59:23 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	flag_d(t_clist *stack_a, t_clist *stack_b, t_count count)
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

void	flag_c(t_clist *stack_a, t_clist *stack_b, t_count count)
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

void	flag_b(t_clist *stack_a, t_clist *stack_b, t_count count)
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

void	flag_a(t_clist *stack_a, t_clist *stack_b, t_count count)
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
