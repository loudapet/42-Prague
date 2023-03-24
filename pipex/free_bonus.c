/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:06:13 by plouda            #+#    #+#             */
/*   Updated: 2023/03/23 12:25:29 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_paths(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->paths[i])
	{
		free(pipex->paths[i]);
		i++;
	}
	free(pipex->paths[i]);
	free(pipex->paths);
}

void	free_cmd_args(t_pipex pipex)
{
	int	i;

	i = 0;
	while (pipex.cmd_args[i])
	{
		free(pipex.cmd_args[i]);
		i++;
	}
	free(pipex.cmd_args[i]);
	free(pipex.cmd_args);
}
