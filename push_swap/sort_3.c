/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:18:00 by plouda            #+#    #+#             */
/*   Updated: 2023/03/07 12:43:52 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Options which are handled by the function, in the same order:
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
If the stack is already sorted, do nothing.
*/
void	sort_3(t_clist *stack)
{
	int	first;
	int	second;
	int	third;

	first = stack->value;
	second = stack->next->value;
	third = stack->next->next->value;
	if (first < second && second > third && third > first)
	{
		reverse_rotate_a(stack);
		swap_a(stack);
	}
	else if (first > second && second < third && third > first)
		swap_a(stack);
	else if (first < second && second > third && third < first)
		reverse_rotate_a(stack);
	else if (first > second && second < third && third < first)
		rotate_a(stack);
	else if (first > second && second > third && third < first)
	{
		rotate_a(stack);
		swap_a(stack);
	}
}
