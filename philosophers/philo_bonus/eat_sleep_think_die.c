/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_die.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:01:00 by plouda            #+#    #+#             */
/*   Updated: 2023/06/23 12:10:38 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* 
	Stop condition for printf: when mutex for write unlocks at the end of
	the whole iteration in create_threads(), the threads that have been
	waiting activate; we don't want the messages there anymore though, so
	the condition filters out these post-mortem messages.
*/
void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->forks[philo->lfork]);
	print_status("\e[38;5;103mhas taken a fork", philo, UNLOCK);
	pthread_mutex_lock(&philo->env->forks[philo->rfork]);
	print_status("\e[38;5;103mhas taken a fork", philo, UNLOCK);
	pthread_mutex_lock(&philo->env->eat);
	print_status("\e[38;5;202mis eating", philo, UNLOCK);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->env->eat);
	suspend(philo->env->time_to_eat);
	philo->course++;
	pthread_mutex_unlock(&philo->env->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->env->forks[philo->rfork]);
}

void	p_sleep(t_philo *philo)
{
	print_status("\e[38;5;117mis sleeping", philo, UNLOCK);
	suspend(philo->env->time_to_sleep);
}

void	p_think(t_philo *philo)
{
	print_status("\e[38;5;102mis thinking", philo, UNLOCK);
}

void	is_sated(t_philo *philos, t_env *env)
{
	int	i;

	i = 0;
	while (env->limit && i < env->count
		&& philos[i].course >= env->limit)
		i++;
	env->sated = (i == env->count);
}

void	p_die(t_philo *philos, t_env *env)
{
	int	i;

	while (!env->sated)
	{
		i = 0;
		while (i < env->count && env->death == 0)
		{
			pthread_mutex_lock(&env->eat);
			if (get_time() - philos[i].last_meal \
				>= (unsigned long)env->time_to_die)
			{
				print_status("\e[1;38;5;207mdied", &philos[i], LOCK);
				env->death = 1;
			}
			pthread_mutex_unlock(&env->eat);
			i++;
		}
		if (env->death)
			return ;
		is_sated(philos, env);
	}
}
