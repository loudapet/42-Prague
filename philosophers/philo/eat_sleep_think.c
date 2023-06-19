/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:01:00 by plouda            #+#    #+#             */
/*   Updated: 2023/06/19 13:20:53 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"


/* 
	Stop condition for printf: when mutex for write unlocks at the end of
	the whole iteration in create_threads(), the threads that have been waiting
	activate; we don't want the messages there anymore though, so the
	condition filters out these post-mortem messages.
*/
void	print_status(char *msg, t_philo *philo, int lock)
{
	unsigned long	timestamp;

	timestamp = get_time() - philo->env->start_time;
	pthread_mutex_lock(&philo->env->write);
	if (!philo->env->stop)
		printf("%-8lu %i %s\n", timestamp, philo->seat, msg);
	if (lock == 1)
	{
		//printf("Unlocking ...\n");
		pthread_mutex_unlock(&philo->env->write);
	}
}

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->forks[philo->lfork]);
	print_status("has taken a left fork", philo, 1);
	pthread_mutex_lock(&philo->env->forks[philo->rfork]);
	print_status("has taken a right fork", philo, 1);
	pthread_mutex_lock(&philo->env->eat);
	print_status("is eating", philo, 1);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->env->eat);
	suspend(philo->env->time_to_eat);
	philo->course++;
	pthread_mutex_unlock(&philo->env->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->env->forks[philo->rfork]);
}

void	p_sleep(t_philo *philo)
{
	print_status("is sleeping", philo, 1);
	suspend(philo->env->time_to_sleep);
}

void	p_think(t_philo *philo)
{
	print_status("is thinking", philo, 1);
}

void	p_die(t_philo *philo, t_env *env)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < env->count && env->stop == 0)
		{
			pthread_mutex_lock(&env->eat);
			if (get_time() - philo[i].last_meal \
				>= (unsigned long)env->time_to_die)
			{
				print_status("died", &philo[i], 0);
				env->stop = 1;
			}
			pthread_mutex_unlock(&env->eat);
			i++;
		}
		if (env->stop)
			return ;
		i = 0;
		while (env->limit && i < env->count && philo[i].course >= env->limit)
			i++;
	}
}
