/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:31:37 by plouda            #+#    #+#             */
/*   Updated: 2023/03/24 16:06:34 by plouda           ###   ########.fr       */
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

void	close_fds(t_pipex *pipex, int flag)
{
	if (flag == 1)
	{
		if (close(pipex->pipe[READ]) < 0 || close(pipex->pipe[WRITE]) < 0)
			print_error();
	}
	else if (flag == 2)
	{
		if (close(pipex->infile) < 0 || close(pipex->outfile) < 0)
			print_error();
	}
}

void	f_pipex(t_pipex *pipex, char **argv, char **envp)
{
	if (pipe(pipex->pipe) < 0)
		print_error();
	pipex->pid1 = fork();
	if (!pipex->pid1)
		process_cmd_infile(*pipex, argv, envp);
	pipex->pid2 = fork();
	if (!pipex->pid2)
		process_cmd_outfile(*pipex, argv, envp);
	close_fds(pipex, 1);
	waitpid(pipex->pid1, &pipex->status1, 0);
	waitpid(pipex->pid2, &pipex->status2, 0);
}

void	f_pipex_multiple(t_pipex *pipex, char **argv, int argc, char **envp)
{
	int	cmd;

	cmd = 2;
	if (pipe(pipex->pipeold) < 0)
		print_error();
	while (cmd < argc - 1)
	{
		if (pipe(pipex->pipenew) < 0)
			print_error();
		pipex->pid1 = fork();
		if (!pipex->pid1)
		{
			if (cmd == 2)
			{
				dup2(pipex->infile, STDIN_FILENO);
				dup2(pipex->pipenew[1], STDOUT_FILENO);
			}
			else if (cmd == argc - 2)
			{
				dup2(pipex->pipeold[0], STDIN_FILENO);
				dup2(pipex->outfile, STDOUT_FILENO);
			}
			else
			{
				dup2(pipex->pipeold[0], STDIN_FILENO);
				dup2(pipex->pipenew[1], STDOUT_FILENO);
			}
			close(pipex->pipeold[0]);
			close(pipex->pipeold[1]);
			close(pipex->pipenew[0]);
			close(pipex->pipenew[1]);
			if (get_cmd(pipex, argv[cmd]))
			{
				error_msg(pipex->cmd_args[0]);
				free_cmd_args(*pipex);
				free_paths(pipex);
				exit(127);
			}
			write(2, argv[cmd], strlen(argv[cmd]));
			write(2, "\n", 1);
			if (execve(pipex->full_cmd, pipex->cmd_args, envp) < 0)
			{
				print_error();
				free_cmd_args(*pipex);
				free_paths(pipex);
				exit(errno);
			}
		}
		else
		{
			close(pipex->pipeold[0]);
			close(pipex->pipeold[1]);
			pipex->pipeold[0] = pipex->pipenew[0];
			pipex->pipeold[1] = pipex->pipenew[1];
		}
		waitpid(pipex->pid1, &pipex->status1, 0);
		cmd++;
	}
	close(pipex->pipeold[0]);
	close(pipex->pipeold[1]);
	waitpid(-1, &pipex->status2, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc == 5)
	{
		get_fds(&pipex, argc, argv);
		pipex.paths = get_paths(envp);
		f_pipex(&pipex, argv, envp);
		free_paths(&pipex);
		close_fds(&pipex, 2);
		return (WEXITSTATUS(pipex.status2));
	}
	else if (argc > 5)
	{
		get_fds(&pipex, argc, argv);
		pipex.paths = get_paths(envp);
		f_pipex_multiple(&pipex, argv, argc, envp);
		free_paths(&pipex);
		close_fds(&pipex, 2);
		return (WEXITSTATUS(pipex.status2));
	}
	return (1);
}
