/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:52:52 by plouda            #+#    #+#             */
/*   Updated: 2023/06/16 10:40:38 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

struct	s_env;

typedef struct	s_philo
{
	pthread_t		tid;
	struct s_env	*env;
	int				seat;
	int				lfork;
	int				rfork;
	unsigned long	recent_meal;
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
	int				test;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	eat;
}				t_env;

int	ft_atoi(const char *nptr);
unsigned long	get_time(void);
t_env	*init_env(int argc, const char **argv);
void	free_memory(t_env *env);

#endif
