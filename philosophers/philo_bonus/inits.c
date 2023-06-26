/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:40:41 by plouda            #+#    #+#             */
/*   Updated: 2023/06/26 13:34:25 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		env->philos[i].seat = i + 1;
		// env->philos[i].lfork = i;
		// env->philos[i].rfork = i - 1;
		// if (env->philos[i].rfork == -1)
		// 	env->philos[i].rfork = env->count - 1;
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
	}
	return (env);
}

//change docu for semaphores in header
int	init_semaphores(t_env *env)
{
	sem_unlink("Forks");
	sem_unlink("Eat");
	sem_unlink("Write");
	sem_unlink("Death");
	sem_unlink("Stop");
	env->forks = sem_open("Forks", O_CREAT, 00644, env->count);
	env->eat = sem_open("Eat", O_CREAT, 00644, 1);
	env->write = sem_open("Write", O_CREAT, 00644, 1);
	env->death = sem_open("Death", O_CREAT, 00644, 1);
	env->stop = sem_open("Stop", O_CREAT, 00644, 1);
	return (0);
}

int	set_times(t_env *env, int argc, const char **argv)
{
	env->sated = 0;
	env->died = 0;
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
		return (VALIDATION_ERROR);
	return (SUCCESS);
}

int	set_env(t_env *env, int argc, const char **argv)
{
	int		count;

	count = ft_atoi(argv[1]);
	env = alloc_memory(env, count);
	if (!env)
		return (throw_error(ALLOCATION_ERROR));
	if (set_times(env, argc, argv))
	{
		free_memory(env);
		return (throw_error(VALIDATION_ERROR));
	}
	if (init_semaphores(env))
	{
		free_memory(env);
		return (throw_error(RUNTIME_ERROR));
	}
	init_philos(env);
	return (SUCCESS);
}
