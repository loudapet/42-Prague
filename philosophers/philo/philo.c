/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:35:36 by plouda            #+#    #+#             */
/*   Updated: 2023/06/12 14:33:18 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	init_forks(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		pthread_mutex_init(&env->forks[i], NULL);
		i++;
	}
}

void	init_philos(t_env *env)
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
	pthread_mutex_init(&env->write, NULL);
	init_forks(env);
	init_philos(env);
	
	return (env);
}

void	*dinner(void *param)
{
	t_env	*env;
	env = param;
	
	if (env)
		printf("Hello thread!\n");
	return (NULL);
}

void	start_cycle(t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	while (i < env->count)
	{
		pthread_create(&env->philos[i].tid, NULL, &dinner, &env);
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
		start_cycle(env);
	}
}