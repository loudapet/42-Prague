/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:25:09 by plouda            #+#    #+#             */
/*   Updated: 2023/06/20 13:13:48 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_usage(void)
{
	write(2, "\e[96mUsage: ./philo <obligatory args> [optional args] \n", 56);
	write(2, "\e[2;96m<number_of_philosophers> ", 33);
	write(2, "\e[2;96m<time_to_die> <time_to_eat> <time_to_sleep> \n", 53);
	write(2, "\e[2;96m[number_of_times_each_philosopher_must_eat]\n\e[0m", 56);
}

int	throw_error(int error_type)
{
	if (error_type == VALIDATION_ERROR)
		write(2, "\e[91mInvalid argument(s).\n", 27);
	else if (error_type == RUNTIME_ERROR)
		write(2, "\e[91mError occurred at runtime. Please try again.\n", 51);
	else if(error_type == ALLOCATION_ERROR)
		write(2, "\e[91mFailed to allocate memory. Please try again.", 50);
	return (1);
}