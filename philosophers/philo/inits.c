/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:40:41 by plouda            #+#    #+#             */
/*   Updated: 2023/06/16 09:41:28 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutexes(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		pthread_mutex_init(&env->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&env->write, NULL);
	pthread_mutex_init(&env->eating, NULL);
}

static void	init_philos(t_env *env)
{
	int i;

	i = 0;
	while (i < env->count)
	{
		env->philos[i].seat = i + 1;
		env->philos[i].lfork = i + 1;
		env->philos[i].rfork = i;
		if (env->philos[i].rfork == 0)
			env->philos[i].rfork = env->count;
		i++;
	}	
}

t_env	*init_env(int argc, const char **argv)
{
	t_env			*env;

	env = malloc(sizeof(t_env));
	env->count = ft_atoi(argv[1]);
	env->philos = malloc(sizeof(t_philo) * env->count);
	env->forks = malloc(sizeof(pthread_mutex_t) * env->count);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->limit = ft_atoi(argv[5]);
	init_mutexes(env);
	init_philos(env);
	
	return (env);
}