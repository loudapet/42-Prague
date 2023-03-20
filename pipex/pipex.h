/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:31:05 by plouda            #+#    #+#             */
/*   Updated: 2023/03/20 14:26:06 by plouda           ###   ########.fr       */
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
# include "libftprintf/ft_printf.h"
# define READ 0
# define WRITE 1

typedef struct	s_pipex
{
	int		infile;
	int		outfile;
	char	**cmd_args;
	char	*cmd;
	char	*args;
	char	*full_cmd;
	int		pipe[2];
	char	**paths;
}				t_pipex;

int	print_error(void);
void	process_cmd1(t_pipex pipex, char **argv, char **envp);
void	process_cmd2(t_pipex pipex, char **argv, char **envp);

#endif