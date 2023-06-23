/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:00:57 by plouda            #+#    #+#             */
/*   Updated: 2023/06/23 12:12:21 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_digit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

// Starting at 1 because only arguments are relevant
int	is_int(int argc, const char **argv)
{
	int	i;
	int	j;
	int	stop;

	i = 1;
	if (argc == 5)
		stop = 4;
	else
		stop = 5;
	while (i <= stop)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_is_digit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
