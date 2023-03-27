/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:34:21 by plouda            #+#    #+#             */
/*   Updated: 2023/03/27 11:49:48 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	process_cmd(t_pipex *pipex, char *argv, char **envp)
{
	if (get_cmd(pipex, argv))
	{
		error_msg(pipex->cmd_args[0]);
		free_cmd_args(*pipex);
		free_paths(pipex);
		exit(127);
	}
	if (execve(pipex->full_cmd, pipex->cmd_args, envp) < 0)
	{
		print_error();
		free_cmd_args(*pipex);
		free_paths(pipex);
		exit(errno);
	}
}

void	process_cmd_infile(t_pipex pipex, char **argv, char **envp)
{
	if (close(pipex.pipe[READ]) < 0)
		print_error();
	if (dup2(pipex.infile, STDIN_FILENO) < 0
		|| dup2(pipex.pipe[WRITE], STDOUT_FILENO) < 0)
		print_error();
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

void	process_cmd_outfile(t_pipex pipex, char **argv, char **envp)
{
	if (close(pipex.pipe[WRITE]) < 0)
		print_error();
	if (dup2(pipex.outfile, STDOUT_FILENO) < 0
		|| dup2(pipex.pipe[READ], STDIN_FILENO) < 0)
		print_error();
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
