/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_die.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:01:00 by plouda            #+#    #+#             */
/*   Updated: 2023/06/26 17:12:17 by plouda           ###   ########.fr       */
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
	sem_wait(philo->env->eat);
	sem_wait(philo->env->forks);
	print_status("\e[38;5;103mhas taken a fork", philo, UNLOCK);
	sem_wait(philo->env->forks);
	print_status("\e[38;5;103mhas taken a fork", philo, UNLOCK);
	//sem_wait(philo->env->eat) > position prevents deadlock in case everyone grabs one fork;
	print_status("\e[38;5;202mis eating", philo, UNLOCK);
	philo->last_meal = get_time();
	sem_post(philo->env->eat);
	suspend(philo->env->time_to_eat);
	philo->course++;
	sem_post(philo->env->forks);
	sem_post(philo->env->forks);
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
	while (1)
	{
		sem_wait(env->death);
		//sem_wait(env->eat);
		if (get_time() - philo->last_meal \
			>= (unsigned long)env->time_to_die)
		{
			print_status("\e[1;38;5;207mdied", philo, LOCK);
			sem_post(env->stop);
			//sem_post(env->eat);
			env->died = 1;
			exit (0);
			return (NULL);
		}
		sem_post(env->death);
		sem_wait(env->death);
		is_sated(philo, env);
		if (env->sated)
		{
			//sem_wait(philo->env->write);
			sem_post(env->death);
			//sem_post(env->stop);
			return (NULL);
		}
		sem_post(env->death);
	}
	return (NULL);
}

