/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:01:07 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 22:56:56 by plouda           ###   ########.fr       */
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

typedef enum e_color
{
	DEFAULT = -1,
	TOPO = -2,
	RAINBOW = -3,
	SUNRISE = -4
}				t_color;

typedef enum e_proj
{
	ISO,
	TOP,
	SIDE,
	CAB,
	CAV
}				t_proj;

typedef enum e_angle
{
	ALPHA,
	BETA,
	GAMMA
}				t_angle;

typedef struct s_tab
{
	int	***tab;
	int	nrows;
	int	ncols;
	int	map_fd;
	int	validation[2];
}				t_tab;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
	int		color;
}				t_vector;

typedef struct s_map
{
	t_vector	**vmap;
	int			nrows;
	int			ncols;
	float		z_max;
	float		z_min;
	int			clr_flag;
}				t_map;

typedef struct s_line
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

typedef struct s_master
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*instr;
	t_map		*vmap;
	t_tab		*map;
	t_camera	*camera;
	t_cursor	*cursor;
	const char	*path;
}				t_master;

void		print_vectors(t_vector **vmap, int ncols, int nrows);
t_tab		*parse_map(const char *path);
t_map		*tab_to_vect(t_tab *tab);
t_map		*allocate(int nrows, int ncols);
void		print_tab_content(int **map_array, int ncols, int nrows);
void		project(t_master *master);
void		error(void);
void		print_instructions(t_master *master);

/* line.c */
void		calc_direction(t_line *line);
void		calc_err(t_line *line, int *cur_p, int delta, int flag);
t_line		init_vars(t_vector p1, t_vector p2);
int			get_default_clr(int z, float min_z, float max_z, int flag);
int			get_clr(t_line line);

/* projections.c */
void		conv_to_iso(float *x, float *y, float *z);
void		conv_to_side(float *y, float *z);
void		conv_to_cab(float *x, float *y, float *z);
void		conv_to_cav(float *x, float *y, float *z);

/* rotations.c */
void		rot_x(float *y, float *z, double alpha);
void		rot_y(float *x, float *z, double beta);
void		rot_z(float *x, float *y, double gamma);

/* initialize.c */
t_camera	*init_camera(t_master *master);
t_cursor	*init_cursor(t_master *master);
t_tab		*init_tab(const char *path);
mlx_image_t	*init_img(mlx_t *mlx);
t_master	*init_master(mlx_t *mlx, mlx_image_t *img, t_tab *map, t_map *vmap);

/* hooks.c */
void		scrollhook(double xdelta, double ydelta, void *param);
void		keyhook(mlx_key_data_t keydata, void *param);
void		cursor(double xpos, double ypos, void *param);
void		resizehook(int32_t width, int32_t height, void *param);
void		reset_angles(t_camera *camera);

/* parse_map_utils.c */
int			col_count(char **array);
int			row_count(const char *path);
int			validate(int *valid, int new);

/* utils.c */
int			abs_val(int nb);
void		line_swap(t_line *line);
void		free_tab(t_tab tab);
void		free_split(char **str);
void		free_map(t_map *map);
void		free_trimmed_split(char *trim, char **split, char *row, int flag);
void		reset_img(mlx_image_t *img);
double		rad_to_deg(double rad);
double		deg_to_rad(double deg);

/* utils_num.c */
double		rad_to_deg(double rad);
double		deg_to_rad(double deg);
int			abs_val(int nb);

/* key_events_utils.c */
void		flatten(t_master *master, mlx_key_data_t keydata);
void		change_color(t_master *master);
void		change_projection(t_master *master);
void		recenter_camera(t_master *master);
void		reset(t_master *master);

/* create_raster.c */
void		create_raster(mlx_image_t *img, t_map map);

/* create_raster_utils.c */
t_line		init_vars(t_vector p1, t_vector p2);
void		calc_err(t_line *line, int *cur_p, int delta, int flag);
void		calc_direction(t_line *line);

/* palette.c */
int			rainbow_palette(double ratio);
int			topo_palette(double ratio);
int			sunrise_palette(double ratio);

/* project_core.c */
void		scale_and_zoom(t_map *dup, t_camera *camera, int row, int col);
void		shift_to_origin(t_map *dup, t_camera *camera, int row, int col);
void		rotate_xyz(t_map *dup, t_camera *camera, int row, int col);
void		convert_projection(t_map *vmap, t_camera *camera, int row, int col);
void		recenter(t_map *dup, t_master *master, int row, int col);

/* ft_atoi_base.c */
int			ft_atoi_base(const char *str, int base);
#endif