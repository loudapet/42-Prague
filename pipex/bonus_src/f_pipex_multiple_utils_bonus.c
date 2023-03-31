/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pipex_multiple_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:00:44 by plouda            #+#    #+#             */
/*   Updated: 2023/03/31 11:05:13 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

/*
Accepts two fds as arguments, one to be redirected from input and one to output.
Then performs redirection using dup2.
*/
void	dup_in_out(int input, int output)
{
	if (dup2(input, STDIN_FILENO) < 0)
		print_error();
	if (dup2(output, STDOUT_FILENO) < 0)
		print_error();
}

/*
Depending on whether the command accepts input from a file or a pipe,
or whether it outputs to a pipe or to a file, the function enables redirection
of input and output for the respective fds.
*/
void	set_io(t_pipex *pipex, int cmd, int argc)
{
	if ((cmd == 2) || (pipex->heredoc == 1 && cmd == 3))
		dup_in_out(pipex->infile, pipex->pipenew[WRITE]);
	else if (cmd == argc - 2)
		dup_in_out(pipex->pipeold[READ], pipex->outfile);
	else
		dup_in_out(pipex->pipeold[READ], pipex->pipenew[WRITE]);
	close_fds(pipex, old_ends);
	close_fds(pipex, new_ends);
}

void	newfds_to_old(t_pipex *pipex)
{
	pipex->pipeold[READ] = pipex->pipenew[READ];
	pipex->pipeold[WRITE] = pipex->pipenew[WRITE];
}

void	parent(t_pipex *pipex)
{
	close_fds(pipex, old_ends);
	newfds_to_old(pipex);
}
