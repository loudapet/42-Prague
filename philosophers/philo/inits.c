/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:40:41 by plouda            #+#    #+#             */
/*   Updated: 2023/06/20 13:16:32 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		if (pthread_mutex_init(&env->forks[i], NULL))
			return (RUNTIME_ERROR);
		i++;
	}
	if (pthread_mutex_init(&env->write, NULL))
		return (RUNTIME_ERROR);
	if (pthread_mutex_init(&env->eat, NULL))
		return (RUNTIME_ERROR);
	return (SUCCESS);
}

static void	init_philos(t_env *env)
{
	int i;

	i = 0;
	while (i < env->count)
	{
		env->philos[i].seat = i + 1;
		env->philos[i].lfork = i;
		env->philos[i].rfork = i - 1;
		if (env->philos[i].rfork == -1)
			env->philos[i].rfork = env->count - 1;
		env->philos[i].env = env;
		env->philos[i].course = 0;
		i++;
	}	
}

t_env	*alloc_memory(t_env *env, int count)
{
	env->count = count;
	env->philos = malloc(sizeof(t_philo) * env->count);
	if (!env->philos)
	{
		free(env);
		env = NULL;
		return (env);
	}
	env->forks = malloc(sizeof(pthread_mutex_t) * env->count);
	if (!env->forks)
	{
		free(env->philos);
		free(env);
		env = NULL;
		return (env);
	}
	return (env);
}

int	set_times(t_env *env, int argc, const char **argv)
{
	env->sated = 0;
	env->death = 0;
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->limit = ft_atoi(argv[5]);
	else
		env->limit = 0;
	if (env->count < 1 || env->time_to_die < 0 
		|| env->time_to_eat < 0 || env->time_to_sleep < 0 
		|| env->limit < 0)
	{
		free_memory(env);
		return (VALIDATION_ERROR);
	}
	return (SUCCESS);
}

// check is_int beforehand!
int	init_env(t_env *env, int argc, const char **argv)
{
	int		count;

	count = ft_atoi(argv[1]);
	env = alloc_memory(env, count);
	if (!env)
		return (throw_error(ALLOCATION_ERROR));
	if (set_times(env, argc, argv))
		return (throw_error(VALIDATION_ERROR));
	if (init_mutexes(env))
	{
		free_memory(env);
		return (throw_error(RUNTIME_ERROR));
	}
	init_philos(env);
	return (SUCCESS);
}