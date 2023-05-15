/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:01:07 by plouda            #+#    #+#             */
/*   Updated: 2023/05/15 12:59:34 by plouda           ###   ########.fr       */
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
# include "MLX42/MLX42.h"
# define WIDTH 1600
# define HEIGHT 900
# define CLR_DISCO			0x9A1F6AFF
# define CLR_BRICK_RED		0xC2294EFF
# define CLR_FLAMINGO		0xEC4B27FF
# define CLR_JAFFA			0xEF8633FF
# define CLR_SAFFRON		0xF3AF3DFF

typedef enum	e_proj
{
	ISO,
	SIDE,
	CAB,
	CAV
}				t_proj;

typedef struct	s_tab
{
	int	**tab;
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
	t_tab		map;
	t_camera	*camera;
	t_cursor	*cursor;
	const char		*path;
}				t_master;


void print_vectors(t_vector **vmap, int ncols, int nrows);
int get_rgba(int r, int g, int b, int a);
t_tab parse_map(const char *path);
t_map	*tab_to_vect(t_tab *tab);
void	recenter_vertices(t_map *map, mlx_image_t *img);
void	rotate_vertices(t_map *map);
void	scale_vertices(t_map *map, mlx_image_t *img);
void	horizontal_shift(t_map *map, int amount);
void	vertical_shift(t_map *map, int amount);
void	zoom(t_map *map, float amount);
t_mid	get_midpoint(t_map map);
void	rotate_z(t_map *map, int flag);
void	print_tab_content(int **map_array, int ncols, int nrows);
void	rotate_y(t_map *map, int flag);
void	rotate_x(t_map *map, int flag);
void	project(t_master *master);

/* line.c */
void calc_direction(t_line *line);
void calc_err(t_line *line, int *cur_p, int delta, int flag);
t_line init_vars(t_vector p1, t_vector p2);
void draw_line(mlx_image_t *img, t_vector p1, t_vector p2);
void create_raster(mlx_image_t *img, t_map map);
int	get_default_clr(int z, float min_z, float max_z);
int	get_clr(t_line line);

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

#endif