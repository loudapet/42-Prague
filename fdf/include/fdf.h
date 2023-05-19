/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:01:07 by plouda            #+#    #+#             */
/*   Updated: 2023/05/19 19:19:50 by plouda           ###   ########.fr       */
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
# include <unistd.h>
# include <stdlib.h>
# include <memory.h>
# include <limits.h>
# include "MLX42/MLX42.h"
# define WIDTH 1600
# define HEIGHT 900


typedef enum	e_color
{
	DEFAULT = -1,
	TOPO = -2,
	RAINBOW = -3
}				t_color;

typedef enum	e_proj
{
	ISO,
	TOP,
	SIDE,
	CAB,
	CAV
}				t_proj;

typedef struct	s_tab
{
	int	***tab;
	int	nrows;
	int	ncols;
}				t_tab;

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
	int		color;
}				t_vector;

typedef struct	s_map
{
	t_vector 	**vmap;
	int			nrows;
	int			ncols;
	float		z_max;
	float		z_min;
	int			clr_flag;
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
	int	color1;
	int	color2;
}				t_line;

typedef struct	s_mid
{
	float	mid_y;
	float	mid_x;
	float	mid_z;
}				t_mid;

typedef struct	s_limits
{
	float	x_min;
	float	y_min;
	float	x_max;
	float	y_max;
	float	z_max;
}				t_limits;

typedef struct s_camera
{
	double			alpha;
	double			beta;
	double			gamma;
	int				x_offset;
	int				y_offset;
	double			zoom;
	double			z_div;
	int				projection;

}				t_camera;

typedef struct s_cursor
{
	double	x_cur;
	double	y_cur;
	double	x_prev;
	double	y_prev;
}				t_cursor;


typedef struct	s_master
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*instr;
	t_map		*vmap;
	t_tab		*map;
	t_camera	*camera;
	t_cursor	*cursor;
	const char		*path;
}				t_master;


void print_vectors(t_vector **vmap, int ncols, int nrows);
int get_rgba(int r, int g, int b, int a);
t_tab *parse_map(const char *path);
t_map	*tab_to_vect(t_tab *tab);

void	print_tab_content(int **map_array, int ncols, int nrows);
void	project(t_master *master);

/* line.c */
void calc_direction(t_line *line);
void calc_err(t_line *line, int *cur_p, int delta, int flag);
t_line init_vars(t_vector p1, t_vector p2);
void draw_line(mlx_image_t *img, t_vector p1, t_vector p2);
void create_raster(mlx_image_t *img, t_map map);
int	get_default_clr(int z, float min_z, float max_z, int flag);
int	get_clr(t_line line);

/* projections.c */
void	conv_to_iso(float *x, float *y, float *z);
void	conv_to_side(float *y, float *z);
void	conv_to_cab(float *x, float *y, float *z);
void	conv_to_cav(float *x, float *y, float *z);

/* rotations.c */
void	rot_x(float *y, float *z, double alpha);
void	rot_y(float *x, float *z, double beta);
void	rot_z(float *x, float *y, double gamma);

/* camera.c */
t_camera	*init_camera(t_master *master);

/* hooks.c */
void	scrollhook(double xdelta, double ydelta, void* param);
void	keyhook(mlx_key_data_t keydata, void *param);
void	cursor(double xpos, double ypos, void* param);

/* utils.c */
int		abs_val(int nb);
void	ft_swap(t_line *line);
float	max_x(t_map map);
float	min_x(t_map map);
float	max_y(t_map map);
float	min_y(t_map map);
float	max_z(t_map map);
float	min_z(t_map map);
t_limits	get_dimensions(t_map map);
void	free_tab(t_tab tab);
void	free_split(char **str);
void	free_map(t_map *map);
void	reset_img(mlx_image_t *img);
double	rad_to_deg(double rad);
double	deg_to_rad(double deg);

/* palette.c */
int	rainbow_palette(double ratio);
int	topo_palette(double ratio);

/* ft_atoi_base.c */
int	ft_atoi_base(const char *str, int base);
#endif