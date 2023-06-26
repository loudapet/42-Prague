/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:57:19 by plouda            #+#    #+#             */
/*   Updated: 2023/06/26 10:13:35 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <errno.h>

sem_t	*sem;

void	ft_putstr(void)
{
	sem_wait(sem);
	write(1, "Hello\n", 6);
	sem_post(sem);
}

int	main(void)
{
	int	i;

	errno = 0;
	perror("Error");
	i = 0;
	sem = sem_open("SEM_B", O_CREAT, 00644, 1);
	perror("Error");
	while (i < 10)
	{
		ft_putstr();
		i++;
	}
	sem_close(sem);
	sem_unlink("SEM_B");
	return (0);
	
}