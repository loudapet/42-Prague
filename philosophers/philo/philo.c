/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:35:36 by plouda            #+#    #+#             */
/*   Updated: 2023/06/16 09:40:59 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dinner(void *param)
{
	t_env	*env;
	env = param;
	
	if (env)
		printf("Hello thread!\n");
	return (NULL);
}

void	start_loop(t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	while (i < env->count)
	{
		env->philos[i].recent_meal = get_time();
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
		start_loop(env);
	}
}