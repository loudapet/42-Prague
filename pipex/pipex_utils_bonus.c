/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:46:25 by plouda            #+#    #+#             */
/*   Updated: 2023/03/27 11:36:40 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5))
		i++;
	envp[i] = envp[i] + 5;
	paths = ft_split(envp[i], ':');
	return (paths);
}

void	get_fds(t_pipex *pipex, int argc, char **argv)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		print_error();
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (pipex->outfile < 0)
		print_error();
}

void	close_fds(t_pipex *pipex, t_close flag)
{
	if (flag == defpipe)
	{
		if (close(pipex->pipe[READ]) < 0 || close(pipex->pipe[WRITE]) < 0)
			print_error();
	}
	else if (flag == files)
	{
		if (close(pipex->infile) < 0 || close(pipex->outfile) < 0)
			print_error();
	}
	else if (flag == old_ends)
	{
		if (close(pipex->pipeold[READ]) || close(pipex->pipeold[WRITE]))
			print_error();
	}
	else if (flag == new_ends)
	{
		if (close(pipex->pipenew[READ]) || close(pipex->pipenew[WRITE]))
			print_error();
	}
}
