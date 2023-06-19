/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:01:00 by plouda            #+#    #+#             */
/*   Updated: 2023/06/19 17:01:53 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"


/* 
	Stop condition for printf: when mutex for write unlocks at the end of
	the whole iteration in create_threads(), the threads that have been waiting
	activate; we don't want the messages there anymore though, so the
	condition filters out these post-mortem messages. 59m
*/
void	print_status(char *msg, t_philo *philo, int lock)
{
	unsigned long	timestamp;

	timestamp = get_time() - philo->env->start_time;
	pthread_mutex_lock(&philo->env->write);
	if (!philo->env->death && !philo->env->sated)
		printf("\e[38;5;95m%-8lu\e[1;38;5;252m %-2i\e[0m %s\n", timestamp, philo->seat, msg);
	if (lock == 1)
		pthread_mutex_unlock(&philo->env->write);
	
}

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->forks[philo->lfork]);
	print_status("\e[38;5;103mhas taken a fork", philo, 1);
	pthread_mutex_lock(&philo->env->forks[philo->rfork]);
	print_status("\e[38;5;103mhas taken a fork", philo, 1);
	pthread_mutex_lock(&philo->env->eat);
	print_status("\e[38;5;202mis eating", philo, 1);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->env->eat);
	suspend(philo->env->time_to_eat);
	philo->course++;
	pthread_mutex_unlock(&philo->env->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->env->forks[philo->rfork]);
}

void	p_sleep(t_philo *philo)
{
	print_status("\e[38;5;117mis sleeping", philo, 1);
	suspend(philo->env->time_to_sleep);
}

void	p_think(t_philo *philo)
{
	print_status("\e[38;5;102mis thinking", philo, 1);
}

void	p_die(t_philo *philo, t_env *env)
{
	int	i;

	while (!env->sated)
	{
		i = 0;
		while (i < env->count && env->death == 0)
		{
			pthread_mutex_lock(&env->eat);
			if (get_time() - philo[i].last_meal \
				>= (unsigned long)env->time_to_die)
			{
				print_status("\e[1;38;5;207mdied", &philo[i], 0);
				env->death = 1;
			}
			pthread_mutex_unlock(&env->eat);
			i++;
		}
		if (env->death)
			return ;
		i = 0;
		while (env->limit && i < env->count && philo[i].course >= env->limit)
			i++;
		env->sated = (i == env->count);
	}
}
