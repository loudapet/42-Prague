/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:35:36 by plouda            #+#    #+#             */
/*   Updated: 2023/06/26 17:28:53 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *param)
{
	int			i;
	t_philo		*philo;
	pthread_t	death;

	i = 0;
	philo = param;
	pthread_create(&death, NULL, &p_die, philo);
	while (!philo->env->sated && !philo->env->died)
	{
		p_eat(philo);
		p_sleep(philo);
		p_think(philo);
		i++;
	}
	pthread_detach(death);
	return (NULL);
}

/*
	It shall be safe to destroy an initialized mutex that is unlocked.  At‐
	tempting  to  destroy a locked mutex, or a mutex that another thread is
	attempting  to  lock,  or  a  mutex   that   is   being   used   in   a
	pthread_cond_timedwait() or pthread_cond_wait() call by another thread,
	results in undefined behavior.
*/
void	kill_processes(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
		kill(env->philos[i++].pid, SIGKILL);
	sem_close(env->forks);
	sem_close(env->eat);
	sem_close(env->write);
	sem_close(env->death);
	sem_close(env->stop);
	sem_unlink("Forks");
	sem_unlink("Eat");
	sem_unlink("Write");
	sem_unlink("Death");
	sem_unlink("Stop");
}

int	create_processes(t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	while (i < env->count)
	{
		env->philos[i].last_meal = get_time();
		env->philos[i].pid = fork();
		if (!env->philos[i].pid)
		{
			philo_routine(&env->philos[i]);
			exit (0);
		}
		i++;
		//usleep(100);
	}
	i = 0;
	waitpid(-1, NULL, 0);
	while (i < env->count)
	{
		kill(env->philos[i++].pid, SIGKILL);
		/* waitpid(-1, NULL, 0);
		write(2, "Hello\n", 7);
		if (i == env->count - 1)
			sem_post(env->stop);
		i++; */
	}
	//sem_post(env->write);
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
		sem_wait(env->stop);
		if (create_processes(env))
			return (throw_error(RUNTIME_ERROR));
		//sem_wait(env->stop);
		//kill_processes(env);
		free_memory(env);
	}
	else
		print_usage();
	return (0);
}
