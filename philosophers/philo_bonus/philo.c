/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:35:36 by plouda            #+#    #+#             */
/*   Updated: 2023/06/23 10:37:54 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *param)
{
	int		i;
	t_philo	*philo;
	t_env	*env;

	i = 0;
	philo = param;
	env = philo->env;
	if (philo->seat % 2 && env->count > 1)
	{
		p_think(philo);
		suspend(env->time_to_eat);
	}
	while (!env->death && !env->sated)
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
		i++;
	}
	return (NULL);
}

/*
	It shall be safe to destroy an initialized mutex that is unlocked.  At‐
	tempting  to  destroy a locked mutex, or a mutex that another thread is
	attempting  to  lock,  or  a  mutex   that   is   being   used   in   a
	pthread_cond_timedwait() or pthread_cond_wait() call by another thread,
	results in undefined behavior.
*/
void	join_threads(t_env *env)
{
	int	i;

	i = 0;
	if (env->count == 1)
		pthread_detach(env->philos[0].tid);
	else
	{
		while (i < env->count)
		{
			pthread_join(env->philos[i].tid, NULL);
			i++;
		}
	}
	i = 0;
	while (i < env->count)
	{
		pthread_mutex_destroy(&env->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&env->write);
	pthread_mutex_destroy(&env->eat);
}

int	create_threads(t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	while (i < env->count)
	{
		env->philos[i].last_meal = get_time();
		if (pthread_create(&env->philos[i].tid, NULL, \
			&philo_routine, &env->philos[i]))
			return (1);
		i++;
	}
	p_die(env->philos, env);
	pthread_mutex_unlock(&env->write);
	return (0);
}

t_env	*init_env(void)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		env = NULL;
	return (env);
}

int	main(int argc, const char **argv)
{
	t_env	*env;

	if (argc == 5 || argc == 6)
	{
		if (!is_int(argc, argv))
			return (throw_error(VALIDATION_ERROR));
		env = init_env();
		if (!env)
			return (throw_error(ALLOCATION_ERROR));
		if (set_env(env, argc, argv))
			return (1);
		if (create_threads(env))
			return (throw_error(RUNTIME_ERROR));
		join_threads(env);
		free_memory(env);
	}
	else
		print_usage();
	return (0);
}
