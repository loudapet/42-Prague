/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:07:29 by plouda            #+#    #+#             */
/*   Updated: 2023/05/10 11:17:33 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			col++;
		}
		//print_vectors(dup->vmap, vmap->ncols, row);
		row++;
	}
	dup->nrows = vmap->nrows;
	dup->ncols = vmap->ncols;
	return (dup);
}

void	project(t_master *master)
{
	int	row;
	int	col;
	t_map	*vmap;
	t_camera	*camera;
	
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
			vmap->vmap[row][col].z *= camera->zoom;
			// Making origin 0,0 the middle of the object
			vmap->vmap[row][col].x -= vmap->ncols * camera->zoom / 2;
			vmap->vmap[row][col].y -= vmap->nrows * camera->zoom / 2;
			// Rotating camera
			rot_x(&vmap->vmap[row][col].y, &vmap->vmap[row][col].z, camera->alpha);
			rot_y(&vmap->vmap[row][col].x, &vmap->vmap[row][col].z, camera->beta);
			rot_z(&vmap->vmap[row][col].x, &vmap->vmap[row][col].y, camera->gamma);
			// Projecting
			conv_to_iso(&vmap->vmap[row][col].x, &vmap->vmap[row][col].y, &vmap->vmap[row][col].z);
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

/* void	drag_image(double xpos, double ypos, t_master *master)
{
	t_mid	mid;
	t_map	*vmap;
	int		row;
	int		col;

	//printf("X: %f, Y: %f\n", xpos, ypos);
	vmap = master->vmap;
	mid = get_midpoint(*vmap);
	row = 0;
	while (row < vmap->nrows)
	{
		col = 0;
		while (col < vmap->ncols)
		{
			vmap->vmap[row][col].x += -mid.mid_x + (float)xpos;
			vmap->vmap[row][col].y += -mid.mid_y + (float)ypos;
			col++;
		}
		//print_vectors(vmap->vmap, vmap->ncols, row);
		row++;
	}
} */

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
	vmap->path = argv[1];
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		error();

	img = init_img(mlx);
	vmap->img = img;
	master = malloc(sizeof(t_master));
	if (!master)
		return (EXIT_FAILURE);
	master->mlx = mlx;
	master->img = img;
	master->vmap = vmap;
	master->map = map;
	master->camera = init_camera(master);
	master->cursor = init_cursor(master);
	reset_img(img);
	project(master);
	/* recenter_vertices(vmap, img);
	rotate_vertices(vmap);
	recenter_vertices(vmap, img);
	scale_vertices(vmap, img);
	recenter_vertices(vmap, img); */
	//create_raster(img, *vmap);

	
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