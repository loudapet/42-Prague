/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:01:07 by plouda            #+#    #+#             */
/*   Updated: 2023/05/24 11:45:33 by plouda           ###   ########.fr       */
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
# define WIDTH 1280
# define HEIGHT 720

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
	double	x;
	double	y;
	double	z;
	int		color;
}				t_vector;

typedef struct s_map
{
	t_vector	**vmap;
	int			nrows;
	int			ncols;
	int			z_max;
	int			z_min;
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
}				t_master;

/* allocate.c */
t_map		*allocate(int nrows, int ncols);

/* colors.c */
int			get_default_clr(int z, int min_z, int max_z, int flag);
int			get_clr(t_line line);

/* create_raster_utils.c */
t_line		init_vars(t_vector p1, t_vector p2);

/* create_raster.c */
void		create_raster(mlx_image_t *img, t_map vmap);

/* cursor.c */
void		cursor(double xpos, double ypos, void *param);

/* free_items.c */
void		free_trimmed_split(char *trim, char **split, char *row, int flag);
void		free_map(t_map *vmap);
void		free_tab(t_tab *tab);
void		free_split(char **str);

/* ft_atoi_base.c */
int			ft_atoi_base(const char *str, int base);

/* initialize.c */
t_master	*init_master(mlx_t *mlx, mlx_image_t *img, t_tab *map, t_map *vmap);
mlx_image_t	*init_img(mlx_t *mlx);
t_tab		*init_tab(const char *path);
t_cursor	*init_cursor(t_master *master);
t_camera	*init_camera(t_master *master);

/* key_events_actions.c */
void		reset(t_master *master);
void		recenter_camera(t_master *master);
void		change_projection(t_master *master);
void		change_color(t_master *master);
void		flatten(t_master *master, mlx_key_data_t keydata);

/* key_events.c */
void		keyhook(mlx_key_data_t keydata, void *param);

/* main.c */
mlx_t		*init_mlx(void);

/* palette.c */
int			topo_palette(double ratio);
int			rainbow_palette(double ratio);
int			sunrise_palette(double ratio);

/* parse_map_utils.c */
int			validate(int *valid, int new);
int			row_count(const char *path);
int			col_count(char **array);
void		print_tab_content(int **map_array, int ncols, int nrows);

/* parse_map.c */
t_tab		*parse_map(const char *path);

/* print_instructions.c */
void		print_instructions(t_master *master);

/* project_core.c */
void		recenter(t_map *dup, t_master *master, int row, int col);
void		convert_projection(t_map *dup, t_camera *camera, int row, int col);
void		rotate_xyz(t_map *dup, t_camera *camera, int row, int col);
void		shift_to_origin(t_map *dup, t_camera *camera, int row, int col);
void		scale_and_zoom(t_map *dup, t_camera *camera, int row, int col);

/* project.c */
void		project(t_master *master);

/* projections.c */
void		conv_to_iso(double *x, double *y, double *z);
void		conv_to_side(double *y, double *z);
void		conv_to_cab(double *x, double *y, double *z);
void		conv_to_cav(double *x, double *y, double *z);

/* reset_angles.c */
void		reset_angles(t_camera *camera);

/* resize.c */
void		resizehook(int32_t width, int32_t height, void *param);

/* rotations.c */
void		rot_x(double *y, double *z, double alpha);
void		rot_y(double *x, double *z, double beta);
void		rot_z(double *x, double *y, double gamma);

/* scroll.c */
void		scrollhook(double xdelta, double ydelta, void *param);

/* utils_num.c */
int			abs_val(int nb);
double		deg_to_rad(double deg);
double		rad_to_deg(double rad);

/* utils.c */
void		reset_img(mlx_image_t *img);
void		error(void);

/* vectors.c */
t_map	*tab_to_vect(t_tab *tab);
t_vector	**create_vectors(t_vector **vmap, int ***tab, int ncols, int row);

#endif