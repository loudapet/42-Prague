/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 10:46:25 by plouda            #+#    #+#             */
/*   Updated: 2023/03/31 19:59:51 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/*
Parses environment for PATH, returns paths with ':' as the delimiter.
*/
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

/*
Handles input to here_doc. The input operation is only interrupted if
the input consists of and only of DELIMITER passed as the second argument
to the program.
*/
void	here_doc(t_pipex *pipex, int argc, char **argv)
{
	int		fd_tmp;
	char	*str;
	int		pipe_counter;

	pipe_counter = -1;
	fd_tmp = pipe(pipex->pipe);
	if (fd_tmp < 0)
		print_error();
	while (++pipe_counter < argc - 5)
		write(STDOUT_FILENO, "pipe ", 5);
	write(STDOUT_FILENO, "heredoc> ", 9);
	str = get_next_line(0);
	while (ft_strncmp(argv[2], str, ft_strlen(argv[2]) != 0)
			|| ft_strncmp(argv[2], str, ft_strlen(argv[2]) + 1) != -10)
	{
		pipe_counter = -1;
		while (++pipe_counter < argc - 5)
			write(STDOUT_FILENO, "pipe ", 5);
		write(STDOUT_FILENO, "heredoc> ", 9);
		write(pipex->pipe[WRITE], str, ft_strlen(str));
		free(str);
		str = get_next_line(0);
	}
	free(str);
	close(pipex->pipe[WRITE]);
}

/*
Assigns fds to the input and output files. Infile must be an existing
file with necessary rights for reading, or a here_doc. If outfile with
the same path already exists, its size is reduced to 0 before any
output is written inside. If a here_doc is present as the infile,
the outfile will not get truncated and is opened in append mode instead.
*/
void	get_fds(t_pipex *pipex, int argc, char **argv)
{
	char	*in;
	char	*out;

	in = argv[1];
	out = argv[argc - 1];
	if (pipex->heredoc == 1)
		pipex->outfile = open(out, O_CREAT | O_WRONLY | O_APPEND, 00644);
	else
		pipex->outfile = open(out, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (pipex->outfile < 0)
		print_error();
	if (pipex->heredoc == 1)
	{
		here_doc(pipex, argc, argv);
		pipex->infile = pipex->pipe[READ];
	}
	else
		pipex->infile = open(in, O_RDONLY);
	if (pipex->infile < 0)
	{
		print_error();
		pipex->infile = open(".in.tmp", O_CREAT | O_RDONLY, 00644);
	}
}

/*
Depending on the flag (as specified by e_close), the function closes
respective fds of pipes or in/outfiles.
*/
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
		if (!access(".in.tmp", 0))
			unlink(".in.tmp");
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
