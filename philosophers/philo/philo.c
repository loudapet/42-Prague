/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:35:36 by plouda            #+#    #+#             */
/*   Updated: 2023/06/16 11:23:53 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *param)
{
	t_philo	*philo;
	t_env	*env;
	
	philo = param;
	env = philo->env;

	//printf("Hello thread ID %lu!\n", philo->tid);
	printf("Hello thread no. %i!\n", philo->env->test);
	pthread_mutex_unlock(&env->write);
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
	while (i < env->count)
	{
		pthread_join(env->philos[i].tid, NULL);
		i++;
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

void	create_threads(t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	while (i < env->count)
	{
		env->philos[i].recent_meal = get_time();
		pthread_mutex_lock(&env->write);
		env->test = i;
		printf("I am a thread no. %i\n", i);
		pthread_create(&env->philos[i].tid, NULL, &philo_routine, &env->philos[i]);
		i++;
	}
}

// protecc mallocs!
int	main(int argc, const char **argv)
{
	t_env	*env;
	if (argc == 5 || argc == 6)
	{
		env = init_env(argc, argv);
		create_threads(env);
		join_threads(env);
		free_memory(env);
	}
}