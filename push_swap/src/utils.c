/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:58:58 by plouda            #+#    #+#             */
/*   Updated: 2023/03/13 15:16:04 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

long	ft_atoi_long(const char *nptr)
{
	unsigned int	i;
	unsigned long	flag;
	long			res;

	i = 0;
	flag = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{	
		flag = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + (nptr[i] - '0');
		i++;
	}
	return (flag * res);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != 0)
		i++;
	return (i);
}

char	**parse_args(char *str)
{
	char	**args;

	args = ft_split(str, ' ');
	return (args);
}

void	free_args(char **args)
{
	int	i;
	int	size;

	i = 0;
	size = count_args(args);
	while (i < size)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_stack(t_clist **stack)
{
	t_clist	*next;
	t_clist	*tmp;

	if (stack && *stack)
	{
		next = (*stack)->next;
		while (next && (next != *stack))
		{
			tmp = next;
			next = next->next;
			free(tmp);
		}
		free(*stack);
		*stack = NULL;
	}
}
