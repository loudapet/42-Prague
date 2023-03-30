/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:31:05 by plouda            #+#    #+#             */
/*   Updated: 2023/03/30 09:48:41 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include "libftprintf/ft_printf.h"
# define READ 0
# define WRITE 1

typedef enum e_close
{
	defpipe = 1,
	files = 2,
	old_ends = 3,
	new_ends = 4
}			t_close;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**cmd_args;
	char	*cmd;
	char	*args;
	char	*full_cmd;
	int		pipe[2];
	int		pipeold[2];
	int		pipenew[2];
	char	**paths;
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;
	int		heredoc;
}				t_pipex;

int		print_error(void);
void	error_msg(char *c);
void	process_cmd_infile(t_pipex pipex, char **argv, char **envp);
void	process_cmd_outfile(t_pipex pipex, char **argv, char **envp);
void	free_paths(t_pipex *pipex	);
void	free_cmd_args(t_pipex pipex);
int		get_cmd(t_pipex *pipex, char *argv);
void	close_fds(t_pipex *pipex, t_close flag);
void	get_fds(t_pipex *pipex, int argc, char **argv);
char	**get_paths(char **envp);
void	process_cmd(t_pipex *pipex, char *argv, char **envp);
void	dup_in_out(int input, int output);
void	set_io(t_pipex *pipex, int cmd, int argc);
void	newfds_to_old(t_pipex *pipex);
void	parent(t_pipex *pipex);

#endif