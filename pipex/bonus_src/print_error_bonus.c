/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 11:22:25 by plouda            #+#    #+#             */
/*   Updated: 2023/04/03 10:12:38 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	print_error(void)
{
	perror("Error");
	return (1);
}

void	error_msg(char *c)
{
	write(2, "pipex: ", 7);
	write(2, "command not found: ", 20);
	write(2, c, ft_strlen(c));
	write(2, "\n", 1);
}
