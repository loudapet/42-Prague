/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:01:07 by plouda            #+#    #+#             */
/*   Updated: 2023/04/21 18:02:15 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include <string.h>
# include "../libftprintf/ft_printf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

typedef struct	s_tab
{
	int	**tab;
	int	nrows;
	int	ncols;
}				t_tab;

typedef struct	s_vector
{
	int	x;
	int	y;
	int	z;
	int	t;
}				t_vector;

typedef struct	s_map
{
	t_vector 	**vmap;
	int			nrows;
	int			ncols;
}				t_map;

typedef struct	s_line
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	cur_x;
	int	cur_y;
	int	flag_x;
	int	flag_y;
	int	dx;
	int	dy;
	int	err;
}				t_line;

void	print_vectors(t_vector **vmap, int ncols, int nrows);
int get_rgba(int r, int g, int b, int a);
t_tab parse_map(const char *path);
t_map	tab_to_vect(t_tab tab);

/* utils.c */
int		abs_val(int nb);
void	ft_swap(t_line *line);

#endif