/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:31:37 by plouda            #+#    #+#             */
/*   Updated: 2023/03/30 12:16:00 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	close_fds(pipex, defpipe);
	waitpid(pipex->pid1, &pipex->status1, 0);
	waitpid(pipex->pid2, &pipex->status2, 0);
}

void	f_pipex_multiple(t_pipex *pipex, char **argv, int argc, char **envp)
{
	int	cmd;

	cmd = 2;
	if (pipex->heredoc == 1)
		cmd = 3;
	if (pipe(pipex->pipeold) < 0)
		print_error();
	while (cmd < argc - 1)
	{
		if (pipe(pipex->pipenew) < 0)
			print_error();
		pipex->pid1 = fork();
		if (!pipex->pid1)
		{
			set_io(pipex, cmd, argc);
			process_cmd(pipex, argv[cmd], envp);
		}
		else
			parent(pipex);
		waitpid(pipex->pid1, &pipex->status2, 0);
		cmd++;
	}
	close_fds(pipex, old_ends);
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
		close_fds(&pipex, files);
		return (WEXITSTATUS(pipex.status2));
	}
	else if (argc > 5)
	{
		if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
			pipex.heredoc = 1;
		else
			pipex.heredoc = 0;
		get_fds(&pipex, argc, argv);
		pipex.paths = get_paths(envp);
		f_pipex_multiple(&pipex, argv, argc, envp);
		free_paths(&pipex);
		close_fds(&pipex, files);
		return (WEXITSTATUS(pipex.status2));
	}
	return (1);
}
