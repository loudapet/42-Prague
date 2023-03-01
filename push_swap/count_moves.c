/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:13:22 by plouda            #+#    #+#             */
/*   Updated: 2023/03/01 16:29:52 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// v jakych pripadech pouzit otaceni zaroven (rr, rrr)
int	count_if_double(int	rota_a, int rota_b, int rev_rota_a, int rev_rota_b)
{
	/*code*/
}

int	count_rota(t_clist *stack, int value)
{
	int	i;

	i = 1;
	if (stack->value == value)
		return (0);
	stack = stack->next;
	while (stack->value != value && stack->start != 1)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

int	count_rev_rota(t_clist *stack, int value)
{
	int	i;

	i = 1;
	if (stack->value == value)
		return (0);
	stack = stack->prev;
	while (stack->value != value && stack->start != 1)
	{
		i++;
		stack = stack->prev;
	}
	return (i);
}
