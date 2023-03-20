/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:31:37 by plouda            #+#    #+#             */
/*   Updated: 2023/03/20 16:40:01 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	pid_t	pid1;
	pid_t	pid2;

	if (argc == 5)
	{
		pipex.infile = open(argv[1], O_RDONLY);
		if (pipex.infile < 0)
			return (print_error());
		pipex.outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00644);
		if (pipex.outfile < 0)
			return (print_error());
		if (pipe(pipex.pipe) < 0)
			return (print_error());
		pipex.paths = get_paths(envp);
		pid1 = fork();
		if (!pid1)
			process_cmd1(pipex, argv, envp);
		pid2 = fork();
		if (!pid2)
			process_cmd2(pipex, argv, envp);
		close(pipex.pipe[READ]);
		close(pipex.pipe[WRITE]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		close(pipex.infile);
		close(pipex.outfile);
		free_paths(&pipex);
	}
}
