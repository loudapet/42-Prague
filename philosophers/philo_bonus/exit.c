/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:34:49 by plouda            #+#    #+#             */
/*   Updated: 2023/06/30 14:37:14 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_processes(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->count)
		kill(env->philos[i++].pid, SIGKILL);
}

void	close_semaphores(t_env *env)
{
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

void	check_exit_status(t_env *env)
{
	int	exited;
	int	i;
	int	wstatus;
	int	counter;

	counter = 0;
	wstatus = 0;
	exited = 0;
	while (!exited)
	{
		i = 0;
		while (i < env->count && !exited)
		{
			waitpid(env->philos[i++].pid, &wstatus, WNOHANG);
			if (WEXITSTATUS(wstatus) == DEAD)
				exited = 1;
			else if (WEXITSTATUS(wstatus) == SATED)
			{
				wstatus = 0;
				counter++;
				if (counter == env->count)
					exited = 1;
			}
		}
	}
}
