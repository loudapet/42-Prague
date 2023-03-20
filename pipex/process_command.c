/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 12:34:21 by plouda            #+#    #+#             */
/*   Updated: 2023/03/20 14:43:13 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_cmd(t_pipex *pipex, char *argv)
{
	int		i;

	pipex->cmd_args = ft_split(argv, ' ');
	pipex->cmd = ft_strjoin("/", pipex->cmd_args[0]);
	pipex->args = pipex->cmd_args[1];
	i = 0;
	while (pipex->paths[i])
	{
		pipex->full_cmd = ft_strjoin(pipex->paths[i], pipex->cmd);
		if (!access(pipex->full_cmd, X_OK))
			return (0);
		free(pipex->full_cmd);
		i++;
	}
	return (1);

}

void	process_cmd1(t_pipex pipex, char **argv, char **envp)
{
	close(pipex.pipe[READ]);
	dup2(pipex.infile, 0);
	dup2(pipex.pipe[WRITE], 1);
	if (get_cmd(&pipex, argv[2]))
	{
		write(2, "Error: Command not found\n", 25);
		exit(EXIT_FAILURE);
	}
	execve(pipex.full_cmd, pipex.cmd_args, envp);
}

void	process_cmd2(t_pipex pipex, char **argv, char **envp)
{
	close(pipex.pipe[WRITE]);
	dup2(pipex.outfile, 1);
	dup2(pipex.pipe[READ], 0);
	if (get_cmd(&pipex, argv[3]))
	{
		write(2, "Error: Command not found\n", 25);
		exit(EXIT_FAILURE);
	}
	execve(pipex.full_cmd, pipex.cmd_args, envp);
}
