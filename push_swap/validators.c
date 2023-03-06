/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:53:52 by plouda            #+#    #+#             */
/*   Updated: 2023/03/06 17:16:11 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_int(char **args, int flag)
{
	int	i;
	int	j;
	int	size;

	i = flag;
	size = count_args(args);
	while (i < size)
	{
		j = 0;
		while (args[i][j] != 0)
		{
			if (ft_isdigit(args[i][j]) == 0 && args[i][j] != '-')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_minmax(char **args, int flag)
{
	int		i;
	int		size;
	long	value;

	i = flag;
	size = count_args(args);
	while (i < size)
	{
		value = ft_atoi_long(args[i]);
		if (value > INT_MAX || value < INT_MIN)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_duplicates(t_clist *stack_a)
{
	int	value;
	int	counter;

	stack_a = stack_a->next;
	while (stack_a->start != 1)
	{	
		counter = 0;
		value = stack_a->value;
		while (stack_a->start != 1)
		{
			if (stack_a->next->value == value)
				return (0);
			stack_a = stack_a->next;
			counter++;
		}
		if (counter == 1)
			break ;
		while (counter > 1)
		{
			stack_a = stack_a->prev;
			counter--;
		}
	}
	return (1);
}

int	is_sorted(t_clist *stack)
{
	while (stack->next->start != 1)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
