/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:52:52 by plouda            #+#    #+#             */
/*   Updated: 2023/06/30 14:35:58 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define LOCK 0
# define UNLOCK 1
# define DEAD 10
# define SATED 20

struct	s_env;

/**
 * Contains all information pertaining to a philosopher.
 * 
 * @param pid process ID
 * @param env pointer to the environment structure
 * @param seat identifier of a philosopher, starting from 1
 * @param lfork identifier of the fork located left of the philosopher
 * @param rfork identifier of the fork located right of the philosopher
 * @param last_meal timestamp of the most recent meal in miliseconds
 * @param course number of meals the philosopher has eaten
 */
typedef struct s_philo
{
	pthread_t		pid;
	struct s_env	*env;
	int				seat;
	int				lfork;
	int				rfork;
	unsigned long	last_meal;
	int				course;
}				t_philo;

/**
 * Contains all information controlling the program's execution environment.
 * 
 * @param count number of philosophers
 * @param philos pointer to the array of philosopher structures
 * @param time_to_die if a philosopher didn’t start eating time_to_die
 * milliseconds since the beginning of their last meal or the beginning of
 * the simulation, they die
 * @param time_to_eat the time it takes a philosopher to eat
 * @param time_to_sleep the time it takes a philosopher to sleep
 * @param start_time timestamp of the beginning of the program's execution
 * @param limit the number of meals each philosopher must have eaten for the
 * execution to stop
 * @param sated flag [0, 1] containing the information about whether all
 * philosophers have eaten at least "limit" number of times
 * @param death flag [0, 1] containing the information about whether
 * a philosopher has died
 * @param forks pointer to the array of mutexes representing each fork
 * @param write mutex for writing output to stout
 * @param eat mutex for the act of eating
 */
typedef struct s_env
{
	int				count;
	t_philo			*philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	unsigned long	start_time;
	int				limit;
	int				sated;
	int				died;
	sem_t			*stop;
	sem_t			*death;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*eat;
}				t_env;

typedef enum e_error
{
	SUCCESS = 0,
	RUNTIME_ERROR,
	ALLOCATION_ERROR,
	VALIDATION_ERROR
}				t_error;

/**
 * @brief Get the current time in miliseconds.
 */
unsigned long	get_time(void);

/**
 * @brief Fill the environment structure with relevant data.
 */
int				set_env(t_env *env, int argc, const char **argv);

/**
 * @brief Stop the execution of a thread for time specified by
 * duration.
 *
 * NOTE: due to the imprecise nature of usleep() as well as due
 * to how threads operate under the hood, suspension might not
 * work as expected for smaller values.
 * 
 * @param duration Value in miliseconds specifying the length
 * of suspension.
 */
void			suspend(int duration);

/**
 * @brief Grab left and right forks respectively, and start eating
 * once both forks are held. The philosopher can neither sleep nor
 * think while in this state.
 * 
 * @param philo Pointer to a philosopher struct.
 */
void			p_eat(t_philo *philo);

/**
 * @brief Fall asleep for a set amount of time. The philosopher can
 * neither eat nor think while in this state.
 * 
 * @param philo Pointer to a philosopher struct.
 */
void			p_sleep(t_philo *philo);

/**
 * @brief Think until being able to grab a fork. The philosopher can
 * neither eat nor sleep while in this state.
 * 
 * @param philo Pointer to a philosopher struct.
 */
void			p_think(t_philo *philo);

/**
 * @brief Check if a philosopher has died, and if so, interrupt the
 * execution of the thread.
 * 
 * @details If a philosopher dies, the function initiates a stop condition that
 * will eventually force all threads to stop executing and exit
 * the program. Under the hood, the function locks the writing mutex
 * after displaying the announcement, and never releases the key.
 * 
 * @param philo Pointer to the philosopher array.
 * @param env Pointer to the environment struct.
 */
void			*p_die(void *param);
//void			p_die(t_philo *philos, t_env *env);

/**
 * @brief Check if all philosophers are sated.
 * 
 * @details "Sated", in this case, stands for the following: Each philosopher
 * has eaten at least X number of times, as specified in the optional
 * argument given to the program at the beginning of its execution.
 * 
 * @param philo Pointer to the philosopher array.
 * @param env Pointer to the environment struct.
 */
void			is_sated(t_philo *philos, t_env *env);

/**
 * @brief Execute the routine of a thread.
 * 
 * @details At the beginning, the routine forces every odd-numbered philosopher
 * to think for the amount of time it takes to eat a meal. After such amount
 * of time (or for every even philosopher), it loops through eat-sleep-think
 * until either a philosopher dies, or until every philosopher
 * has eaten  at least X number of times, as specified in the optional
 * argument given to the program at the beginning of its execution.
 * 
 * @param param Pointer to a philosopher struct.
 */
void			*philo_routine(void *param);

/**
 * @details Utilities.
 */
void			print_status(char *msg, t_philo *philo, int lock);
int				throw_error(int error_type);
void			print_usage(void);
void			free_memory(t_env *env);
int				ft_atoi(const char *nptr);
int				is_int(int argc, const char **argv);
void			kill_processes(t_env *env);
void			close_semaphores(t_env *env);
void			check_exit_status(t_env *env);

#endif
