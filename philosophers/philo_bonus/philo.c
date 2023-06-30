/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:35:36 by plouda            #+#    #+#             */
/*   Updated: 2023/06/30 14:35:07 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
./philo 1 800 200 200 - Philosopher should not eat and should die.
./philo 5 800 200 200 - No Philosopher should die.
./philo 5 800 200 200 7 - No Philosopher should die and the simulation
	should stop when every philosopher has eaten at least 7 times.
./philo 4 410 200 200 - No Philosopher should die.
./philo 4 310 200 100 - One Philosopher should die.
./philo 3 400 150 200 1 - One Philosopher should die under normal circumstances,
but won't due to implementation limits.
*/
void	*philo_routine(void *param)
{
	t_philo		*philo;
	pthread_t	death;

	philo = param;
	pthread_create(&death, NULL, &p_die, philo);
	pthread_detach(death);
	if (philo->seat % 2 && philo->env->count > 1)
	{
		p_think(philo);
		suspend(philo->env->time_to_eat);
	}
	while (!philo->env->sated && !philo->env->died)
	{
		p_eat(philo);
		if (philo->env->sated)
			exit (SATED);
		p_sleep(philo);
		if (philo->env->sated)
			exit (SATED);
		p_think(philo);
		if (philo->env->sated)
			exit (SATED);
	}
	return (NULL);
}

// usleep(100) as a bumper
int	create_processes(t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	while (i < env->count)
	{
		env->philos[i].pid = fork();
		if (!env->philos[i].pid)
		{
			env->philos[i].last_meal = get_time();
			philo_routine(&env->philos[i]);
			usleep(100);
		}
		i++;
	}
	check_exit_status(env);
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
		if (create_processes(env))
			return (throw_error(RUNTIME_ERROR));
		kill_processes(env);
		close_semaphores(env);
		free_memory(env);
	}
	else
		print_usage();
	return (0);
}
