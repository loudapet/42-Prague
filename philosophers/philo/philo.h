/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:52:52 by plouda            #+#    #+#             */
/*   Updated: 2023/06/20 12:47:15 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define LOCK 0
# define UNLOCK 1

struct	s_env;

typedef struct	s_philo
{
	pthread_t		tid;
	struct s_env	*env;
	int				seat;
	int				lfork;
	int				rfork;
	unsigned long	last_meal;
	int				course;
}				t_philo;

typedef struct	s_env
{
	int				count;
	t_philo			*philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	unsigned long	start_time;
	int				limit;
	int				sated;
	int				death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	eat;
}				t_env;

typedef enum	e_error
{
	SUCCESS = 0,
	RUNTIME_ERROR,
	ALLOCATION_ERROR,
	VALIDATION_ERROR
}				t_error;

int	ft_atoi(const char *nptr);
unsigned long	get_time(void);
int	init_env(t_env *env, int argc, const char **argv);
void	free_memory(t_env *env);
void	suspend(int duration);
void	p_eat(t_philo *philo);
void	print_status(char *msg, t_philo *philo, int lock);
void	p_sleep(t_philo *philo);
void	p_think(t_philo *philo);
void	p_die(t_philo *philo, t_env *env);
int	throw_error(int error_type);
void	print_usage(void);

#endif
