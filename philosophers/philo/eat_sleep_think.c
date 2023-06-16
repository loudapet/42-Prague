/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:01:00 by plouda            #+#    #+#             */
/*   Updated: 2023/06/16 12:26:51 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	print_status(char *msg, t_philo *philo)
{
	unsigned long	timestamp;

	timestamp = get_time() - philo->env->start_time;
	pthread_mutex_lock(&philo->env->write);
	printf("%lu %i %s\n", timestamp, philo->seat, msg);
	pthread_mutex_unlock(&philo->env->write);
}

void	p_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->env->forks[philo->lfork]);
	print_status("has taken a fork", philo);
	pthread_mutex_lock(&philo->env->forks[philo->rfork]);
	print_status("has taken a fork", philo);
	pthread_mutex_lock(&philo->env->eat);
	print_status("is eating", philo);
	pthread_mutex_unlock(&philo->env->eat);
	suspend(philo->env->time_to_eat);
	pthread_mutex_unlock(&philo->env->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->env->forks[philo->rfork]);
}

void	p_sleep(t_philo *philo)
{
	print_status("is sleeping", philo);
	suspend(philo->env->time_to_sleep);
}

void	p_think(t_philo *philo)
{
	print_status("is thinking", philo);
}
