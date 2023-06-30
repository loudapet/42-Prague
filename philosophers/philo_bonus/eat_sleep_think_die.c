/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_die.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:01:00 by plouda            #+#    #+#             */
/*   Updated: 2023/06/30 14:22:45 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	p_eat(t_philo *philo)
{
	sem_wait(philo->env->forks);
	print_status("\e[38;5;103mhas taken a fork", philo, UNLOCK);
	sem_wait(philo->env->forks);
	print_status("\e[38;5;103mhas taken a fork", philo, UNLOCK);
	sem_wait(philo->env->death);
	print_status("\e[38;5;202mis eating", philo, UNLOCK);
	philo->last_meal = get_time();
	sem_post(philo->env->death);
	suspend(philo->env->time_to_eat);
	sem_post(philo->env->forks);
	sem_post(philo->env->forks);
	philo->course++;
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

void	is_sated(t_philo *philo, t_env *env)
{
	if (env->limit && philo->course >= env->limit)
		env->sated = 1;
}

void	*p_die(void *param)
{
	t_philo	*philo;
	t_env	*env;

	philo = param;
	env = philo->env;
	while (!env->sated)
	{
		sem_wait(env->death);
		if (get_time() - philo->last_meal \
			>= (unsigned long)env->time_to_die)
		{
			print_status("\e[1;38;5;207mdied", philo, LOCK);
			env->died = 1;
			exit (DEAD);
		}
		sem_post(env->death);
		sem_wait(env->death);
		is_sated(philo, env);
		sem_post(env->death);
	}
	return (NULL);
}
