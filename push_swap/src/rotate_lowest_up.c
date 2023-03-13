/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_lowest_up.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:17:39 by plouda            #+#    #+#             */
/*   Updated: 2023/03/13 15:15:58 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
Rotates/reverse rotates the stack rot-times or rev_rot-times
depending on which option is cheaper
*/
static void	move_up(t_clist *stack_a, int rot, int rev_rot)
{
	if (rot > rev_rot)
	{
		while (rev_rot > 0)
		{
			reverse_rotate_a(stack_a);
			rev_rot--;
		}
	}
	else
	{
		while (rot > 0)
		{
			rotate_a(stack_a);
			rot--;
		}
	}
}

/*
Finds the lowest value in the stack and counts the amount of
rotations or reverse rotations needed in order to rotate it
to the top of the stack, then executes the moves.
*/
void	rotate_lowest_up(t_clist **stack_a)
{
	int	rot;
	int	rev_rot;

	while ((*stack_a)->value != min_value(*stack_a))
		*stack_a = (*stack_a)->next;
	rot = count_rota_a(*stack_a);
	rev_rot = count_rev_rota_a(*stack_a);
	while ((*stack_a)->start != 1)
		*stack_a = (*stack_a)->next;
	move_up(*stack_a, rot, rev_rot);
}
