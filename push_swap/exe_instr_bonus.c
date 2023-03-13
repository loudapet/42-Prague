/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_instr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:38:23 by plouda            #+#    #+#             */
/*   Updated: 2023/03/13 11:30:25 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	instr_len(char *instr)
{
	int	i;

	i = 0;
	while (instr[i] != '\n' && instr[i] != '\0')
		i++;
	return (i);
}

void	exe_instr(char *instr, t_clist **stack_a, t_clist **stack_b)
{
	//ft_printf("%d\n", instr_len(instr));
	if (instr_len(instr) == 2)
	{
		if (!ft_strncmp(instr, "sa", 2))
			swap(*stack_a);
		else if (!ft_strncmp(instr, "sb", 2))
			swap(*stack_b);
		else if (!ft_strncmp(instr, "ss", 2))
		{
			swap(*stack_a);
			swap(*stack_b);
		}
		else if (!ft_strncmp(instr, "pa", 2))
			push(stack_b, stack_a);
		else if (!ft_strncmp(instr, "pb", 2))
			push(stack_a, stack_b);
		else if (!ft_strncmp(instr, "ra", 2))
			rotate(*stack_a);
		else if (!ft_strncmp(instr, "rb", 2))
			rotate(*stack_b);
		else if (!ft_strncmp(instr, "rr", 2))
		{
			rotate(*stack_a);
			rotate(*stack_b);
		}
	}
	else
	{
		if (!ft_strncmp(instr, "rra", 3))
			reverse_rotate(*stack_a);
		else if (!ft_strncmp(instr, "rrb", 3))
			reverse_rotate(*stack_b);
		else if (!ft_strncmp(instr, "rrr", 3))
		{
			reverse_rotate(*stack_a);
			reverse_rotate(*stack_b);
		}
	}
}