/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pipex_multiple_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:00:44 by plouda            #+#    #+#             */
/*   Updated: 2023/03/30 09:49:42 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	dup_in_out(int input, int output)
{
	if (dup2(input, STDIN_FILENO) < 0)
		print_error();
	if (dup2(output, STDOUT_FILENO) < 0)
		print_error();
}

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