/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:52:52 by plouda            #+#    #+#             */
/*   Updated: 2023/06/12 14:06:26 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_philo
{
	pthread_t	tid;
	int	seat;
	int	lfork;
	int	rfork;
}				t_philo;

typedef struct	s_env
{
	int				count;
	t_philo			*philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
	int				limit;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
}				t_env;

int	ft_atoi(const char *nptr);

#endif
