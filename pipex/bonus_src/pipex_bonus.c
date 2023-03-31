/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:31:37 by plouda            #+#    #+#             */
/*   Updated: 2023/03/31 11:03:59 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/*
For two pipes, the program uses two children and a parent supervisor.
The first child reads on STDIN from input file, executes the command and
redirects the output to a pipe.
The second child reads the output of the previous command from the pipe,
executes the next command and redirects the output to output file.
The parent is just there to wait for children to finish.
*/
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

/*
For more than two pipes, the program uses only two alternating sets of pipes:
pipeold, pipenew. The loop creates a new pipe, then forks. The child process
handles reading from and writing into pipeold and pipenew respectively (which
means that pipeold[WRITE] and pipenew[READ] are actually never used), as well
as executing the command. The parent simply closes the old pipe and forces
the current new pipe to become an old pipe. 
*/
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
		parent(pipex);
		waitpid(pipex->pid1, &pipex->status2, 0);
		cmd++;
	}
}

/*
Primarily a dispatching function. Handling multiple pipes
uses a different set of moves than handling just two.
*/
int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc == 5)
	{
		pipex.heredoc = 0;
		get_fds(&pipex, argc, argv);
		pipex.paths = get_paths(envp);
		f_pipex(&pipex, argv, envp);
		free_paths(&pipex);
		close_fds(&pipex, files);
		return (WEXITSTATUS(pipex.status2));
	}
	else if (argc > 5)
	{
		pipex.heredoc = 0;
		if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
			pipex.heredoc = 1;
		get_fds(&pipex, argc, argv);
		pipex.paths = get_paths(envp);
		f_pipex_multiple(&pipex, argv, argc, envp);
		free_paths(&pipex);
		close_fds(&pipex, files);
		return (WEXITSTATUS(pipex.status2));
	}
	return (1);
}
