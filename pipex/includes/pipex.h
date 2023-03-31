/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:31:05 by plouda            #+#    #+#             */
/*   Updated: 2023/03/31 11:04:35 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include "../libftprintf/ft_printf.h"
# define READ 0
# define WRITE 1

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**cmd_args;
	char	*cmd;
	char	*args;
	char	*full_cmd;
	int		pipe[2];
	char	**paths;
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;
}				t_pipex;

int		print_error(void);
void	error_msg(char *c);
void	process_cmd1(t_pipex pipex, char **argv, char **envp);
void	process_cmd2(t_pipex pipex, char **argv, char **envp);
void	free_paths(t_pipex *pipex);
void	free_cmd_args(t_pipex pipex);

#endif