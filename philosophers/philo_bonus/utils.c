/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 10:01:14 by plouda            #+#    #+#             */
/*   Updated: 2023/06/30 14:23:34 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(char *msg, t_philo *philo, int lock)
{
	unsigned long	timestamp;

	timestamp = get_time() - philo->env->start_time;
	sem_wait(philo->env->write);
	if (!philo->env->died)
		printf("\e[38;5;95m%-15lu\e[1;38;5;252m %i\e[0m %s\e[0m\n", \
		timestamp, philo->seat, msg);
	if (lock == 1)
		sem_post(philo->env->write);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	unsigned int	flag;
	unsigned int	res;

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

unsigned long	get_time(void)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	suspend(int duration)
{
	unsigned long	start_time;

	start_time = get_time();
	while (get_time() - start_time < (unsigned long)duration)
		usleep(1);
}

void	free_memory(t_env *env)
{
	free(env->philos);
	free(env);
	env = NULL;
}
