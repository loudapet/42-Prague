/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:07:29 by plouda            #+#    #+#             */
/*   Updated: 2023/05/15 13:16:54 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_instructions(t_master *master)
{
	master->instr = mlx_put_string(master->mlx, "Reset:             R",15,5);
	master->instr = mlx_put_string(master->mlx, "Move:     Arrow Keys",15,25);
	master->instr = mlx_put_string(master->mlx, "Zoom:         Scroll",15,45);
	master->instr = mlx_put_string(master->mlx, "Rotate z:        Q/E",15,65);
	master->instr = mlx_put_string(master->mlx, "Rotate y:        A/D",15,85);
	master->instr = mlx_put_string(master->mlx, "Rotate x:        W/S",15,105);
	master->instr = mlx_put_string(master->mlx, "Recenter:          C",15,125);
	master->instr = mlx_put_string(master->mlx, "Flatten/raise:	  Z/X",15,145);
	master->instr = mlx_put_string(master->mlx, "Change projection: P",15,165);
	master->instr = mlx_put_string(master->mlx, "ISO, SIDE, CAB, CAV",15,195);
}

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

mlx_image_t *init_img(mlx_t *mlx)
{
	mlx_image_t *img;

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		error();
	return (img);
}

static void	rot_x(float *y, float *z, double alpha)
{
	float	prev_y;

	prev_y = *y;
	*y = prev_y * cos(alpha) + (*z) * sin(alpha);
	*z = -prev_y * sin(alpha) + (*z) * cos(alpha);
}

static void	rot_y(float *x, float *z, double beta)
{
	float	prev_x;

	prev_x = *x;
	*x = prev_x * cos(beta) + (*z) * sin(beta);
	*z = -prev_x * sin(beta) + (*z) * cos(beta);
}

static void	rot_z(float *x, float *y, double gamma)
{
	float	prev_x;
	float	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = prev_x * cos(gamma) - prev_y * sin(gamma);
	*y = prev_x * sin(gamma) + prev_y * cos(gamma);
}

static void	conv_to_iso(float *x, float *y, float *z)
{
	float	prev_x;
	float	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.5236);
	*y = (prev_x + prev_y) * sin(0.5236) - (*z);
}

static void	conv_to_side(float *y, float *z)
{
	float	prev_y;
	float	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(1.57) - prev_z * sin(1.57);
	*z = prev_y * sin(1.57) + prev_z * cos(1.57);
}

static void	conv_to_cab(float *x, float *y, float *z)
{
	float	prev_x;
	float	prev_y;
	float	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(1.57) - prev_z * sin(1.57);
	*z = prev_y * sin(1.57) + prev_z * cos(1.57);
	prev_x = *x;
	prev_y = *y;
	*x = prev_x + (*z) * cos(1) * 0.5;
	*y = prev_y + (*z) * sin(1) * 0.5;
}

static void	conv_to_cav(float *x, float *y, float *z)
{
	float	prev_x;
	float	prev_y;
	float	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(1.57) - prev_z * sin(1.57);
	*z = prev_y * sin(1.57) + prev_z * cos(1.57);
	prev_x = *x;
	prev_y = *y;
	*x = prev_x + (*z) * cos(1);
	*y = prev_y + (*z) * sin(1);
}

static t_map	*vectdup(t_map *vmap)
{
	t_map	*dup;
	int		row;
	int		col;

	dup = malloc(sizeof(t_map));
	if (!dup)
	{
		dup = NULL;
		return (dup);
	}
	dup->vmap = malloc(sizeof(t_vector *) * vmap->nrows);
	row = 0;
	while (row < vmap->nrows)
	{
		dup->vmap[row] = malloc(sizeof(t_vector) * vmap->ncols);
		col = 0;
		while (col < vmap->ncols)
		{
			dup->vmap[row][col].x = vmap->vmap[row][col].x;
			dup->vmap[row][col].y = vmap->vmap[row][col].y;
			dup->vmap[row][col].z = vmap->vmap[row][col].z;
			dup->vmap[row][col].color = vmap->vmap[row][col].color;
			col++;
		}
		//print_vectors(dup->vmap, vmap->ncols, row);
		row++;
	}
	dup->nrows = vmap->nrows;
	dup->ncols = vmap->ncols;
	return (dup);
}

void	convert_projection(t_map *vmap, int projection, int row, int col)
{
	float	*x;
	float	*y;
	float	*z;

	x = &vmap->vmap[row][col].x;
	y = &vmap->vmap[row][col].y;
	z = &vmap->vmap[row][col].z;
	if (projection == ISO)
		conv_to_iso(x, y, z);
	if (projection == SIDE)
		conv_to_side(y, z);
	if (projection == CAB)
		conv_to_cab(x, y, z);
	if (projection == CAV)
		conv_to_cav(x, y, z);
}

void	project(t_master *master)
{
	int	row;
	int	col;
	t_map	*vmap;
	t_camera	*camera;
	
	reset_img(master->img);
	vmap = vectdup(master->vmap);
	camera = master->camera;
	row = 0;
	while (row < vmap->nrows)
	{
		col = 0;
		while (col < vmap->ncols)
		{
			// Scaling/zooming
			vmap->vmap[row][col].x *= camera->zoom;
			vmap->vmap[row][col].y *= camera->zoom;
			vmap->vmap[row][col].z *= camera->zoom / camera->z_div;
			// Making origin 0,0 the middle of the object
			vmap->vmap[row][col].x -= vmap->ncols * camera->zoom / 2;
			vmap->vmap[row][col].y -= vmap->nrows * camera->zoom / 2;
			// Rotating camera
			rot_x(&vmap->vmap[row][col].y, &vmap->vmap[row][col].z, camera->alpha);
			rot_y(&vmap->vmap[row][col].x, &vmap->vmap[row][col].z, camera->beta);
			rot_z(&vmap->vmap[row][col].x, &vmap->vmap[row][col].y, camera->gamma);
			// Projecting
			convert_projection(vmap, camera->projection, row, col);
			// Recentering
			vmap->vmap[row][col].x += (int)master->img->width / 2 + camera->x_offset;
			vmap->vmap[row][col].y += (int)master->img->height / 2 + camera->y_offset;
			// Calibration (not needed)
			//vmap->vmap[row][col].y += vmap->ncols * camera->zoom * 2 / 5;
			col++;
		}
		//print_vectors(vmap->vmap, vmap->ncols, row);	
		row++;
	}
	create_raster(master->img, *vmap);
	free_map(vmap);
}

t_cursor	*init_cursor(t_master *master)
{
	t_cursor	*cursor;
	int32_t			x;
	int32_t			y;

	cursor = (t_cursor *)malloc(sizeof(t_cursor));
	mlx_get_mouse_pos(master->mlx, &x, &y);
	cursor->x_cur = x;
	cursor->y_cur = y;
	cursor->x_prev = x;
	cursor->y_prev = y;
	return (cursor);
}

int32_t main(int argc, const char **argv)
{
	t_tab map;
	t_map *vmap;
	mlx_image_t *img;
	mlx_t *mlx;
	t_master	*master;

	if (argc == 2)
		map = parse_map(argv[1]);
	if (!map.tab)
		return (EXIT_FAILURE);
	vmap = tab_to_vect(&map);
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		error(); 	

	img = init_img(mlx);
	master = malloc(sizeof(t_master));
	if (!master)
		return (EXIT_FAILURE);
	master->mlx = mlx;
	master->img = img;
	master->vmap = vmap;
	master->map = map;
	master->camera = init_camera(master);
	master->cursor = init_cursor(master);
	project(master);
	print_instructions(master);
	
	mlx_key_hook(mlx, &keyhook, master);
	mlx_scroll_hook(mlx, &scrollhook, master);
	mlx_cursor_hook(mlx, &cursor, master);
	mlx_loop(mlx);

	mlx_delete_image(master->mlx, img);
	mlx_terminate(master->mlx);
	free_tab(map);
	free_map(vmap);
	free(master->camera);
	free(master->cursor);
	free(master);
	return (EXIT_SUCCESS);
}