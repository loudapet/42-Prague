/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:34:21 by plouda            #+#    #+#             */
/*   Updated: 2023/03/23 10:00:53 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_cmd(t_pipex *pipex, char *argv)
{
	int		i;

	pipex->cmd_args = ft_split(argv, ' ');
	if (!access(pipex->cmd_args[0], X_OK))
	{
		pipex->full_cmd = pipex->cmd_args[0];
		return (0);
	}
	pipex->cmd = ft_strjoin("/", pipex->cmd_args[0]);
	pipex->args = pipex->cmd_args[1];
	i = 0;
	while (pipex->paths[i])
	{
		pipex->full_cmd = ft_strjoin(pipex->paths[i], pipex->cmd);
		if (!access(pipex->full_cmd, X_OK))
		{
			free(pipex->cmd);
			return (0);
		}
		free(pipex->full_cmd);
		i++;
	}
	free(pipex->cmd);
	return (1);
}

void	process_cmd1(t_pipex pipex, char **argv, char **envp)
{
	close(pipex.pipe[READ]);
	dup2(pipex.infile, 0);
	dup2(pipex.pipe[WRITE], 1);
	if (get_cmd(&pipex, argv[2]))
	{
		error_msg(pipex.cmd_args[0]);
		free_cmd_args(pipex);
		free_paths(&pipex);
		exit(127);
	}
	if (execve(pipex.full_cmd, pipex.cmd_args, envp) < 0)
	{
		print_error();
		free_cmd_args(pipex);
		free_paths(&pipex);
		exit(errno);
	}
}

void	process_cmd2(t_pipex pipex, char **argv, char **envp)
{
	close(pipex.pipe[WRITE]);
	dup2(pipex.outfile, 1);
	dup2(pipex.pipe[READ], 0);
	if (get_cmd(&pipex, argv[3]))
	{
		error_msg(pipex.cmd_args[0]);
		free_cmd_args(pipex);
		free_paths(&pipex);
		exit(127);
	}
	if (execve(pipex.full_cmd, pipex.cmd_args, envp) < 0)
	{
		print_error();
		free_cmd_args(pipex);
		free_paths(&pipex);
		exit(errno);
	}
}
