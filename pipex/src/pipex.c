/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:31:37 by plouda            #+#    #+#             */
/*   Updated: 2023/03/31 18:45:07 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
	pipex->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (pipex->outfile < 0)
		print_error();
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
	{
		print_error();
		pipex->infile = open(".in.tmp", O_CREAT | O_RDONLY, 00644);
	}
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
		if (!access(".in.tmp", 0))
			unlink(".in.tmp");
	}
}

void	f_pipex(t_pipex *pipex, char **argv, char **envp)
{
	if (pipe(pipex->pipe) < 0)
		print_error();
	pipex->pid1 = fork();
	if (!pipex->pid1)
		process_cmd1(*pipex, argv, envp);
	pipex->pid2 = fork();
	if (!pipex->pid2)
		process_cmd2(*pipex, argv, envp);
	close_fds(pipex, 1);
	waitpid(pipex->pid1, &pipex->status1, 0);
	waitpid(pipex->pid2, &pipex->status2, 0);
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
		if (WEXITSTATUS(pipex.status2) == 13)
			return (126);
		return (WEXITSTATUS(pipex.status2));
	}
	return (1);
}
