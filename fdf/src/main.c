/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:07:29 by plouda            #+#    #+#             */
/*   Updated: 2023/05/19 20:10:37 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_instructions(t_master *master)
{
	int32_t	x;

	x = 15;
	master->instr = mlx_put_string(master->mlx, "Reset:            R", x, 5);
	master->instr = mlx_put_string(master->mlx, "Move:    Arrow Keys", x, 25);
	master->instr = mlx_put_string(master->mlx, "Zoom:        Scroll", x, 45);
	master->instr = mlx_put_string(master->mlx, "Rotate z:       Q/E", x, 65);
	master->instr = mlx_put_string(master->mlx, "Rotate y:       A/D", x, 85);
	master->instr = mlx_put_string(master->mlx, "Rotate x:       W/S", x, 105);
	master->instr = mlx_put_string(master->mlx, "Flatten/raise:  Z/X", x, 125);
	master->instr = mlx_put_string(master->mlx, "Recenter:         T", x, 145);
	master->instr = mlx_put_string(master->mlx, "Change color:     C", x, 165);
	master->instr = mlx_put_string(master->mlx, "Swap projection:  P", x, 185);
	master->instr = mlx_put_string(master->mlx, "ISOMETRIC          ", x, 215);
	master->instr = mlx_put_string(master->mlx, "TOP VIEW           ", x, 235);
	master->instr = mlx_put_string(master->mlx, "SIDE VIEW          ", x, 255);
	master->instr = mlx_put_string(master->mlx, "CABINET            ", x, 275);
	master->instr = mlx_put_string(master->mlx, "CAVALIER           ", x, 295);
}

static void	error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

mlx_image_t	*init_img(mlx_t *mlx)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		error();
	return (img);
}

static t_map	*vectdup(t_map *vmap, int **tab)
{
	t_map	*dup;
	int		row;
	int		col;
	int		clr;

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
			if (tab[row][col] > -4 && tab[row][col] < 0)
			{
				clr = vmap->clr_flag;
				dup->vmap[row][col].color = \
				get_default_clr(dup->vmap[row][col].z, \
				vmap->z_min, vmap->z_max, clr);
			}
			else
				dup->vmap[row][col].color = tab[row][col];
			col++;
		}
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
	if (projection == TOP)
		return ;
	if (projection == SIDE)
		conv_to_side(y, z);
	if (projection == CAB)
		conv_to_cab(x, y, z);
	if (projection == CAV)
		conv_to_cav(x, y, z);
}

/*
1. Scaling/zooming
2. Making origin 0,0 the middle of the object
3. Rotating camera (XYZ)
4. Projecting
5. Recentering
*/
void	project(t_master *master)
{
	int			row;
	int			col;
	t_map		*vmap;
	t_camera	*camera;

	reset_img(master->img);
	vmap = vectdup(master->vmap, master->map->tab[1]);
	camera = master->camera;
	row = 0;
	while (row < vmap->nrows)
	{
		col = 0;
		while (col < vmap->ncols)
		{
			vmap->vmap[row][col].x *= camera->zoom;
			vmap->vmap[row][col].y *= camera->zoom;
			vmap->vmap[row][col].z *= camera->zoom / camera->z_div;
			vmap->vmap[row][col].x -= vmap->ncols * camera->zoom / 2;
			vmap->vmap[row][col].y -= vmap->nrows * camera->zoom / 2;
			rot_x(&vmap->vmap[row][col].y, &vmap->vmap[row][col].z, camera->alpha);
			rot_y(&vmap->vmap[row][col].x, &vmap->vmap[row][col].z, camera->beta);
			rot_z(&vmap->vmap[row][col].x, &vmap->vmap[row][col].y, camera->gamma);
			convert_projection(vmap, camera->projection, row, col);
			vmap->vmap[row][col].x += (int)master->img->width / 2 + camera->x_offset;
			vmap->vmap[row][col].y += (int)master->img->height / 2 + camera->y_offset;
			col++;
		}
		row++;
	}
	create_raster(master->img, *vmap);
	free_map(vmap);
}

t_cursor	*init_cursor(t_master *master)
{
	t_cursor	*cursor;
	int32_t		x;
	int32_t		y;

	cursor = (t_cursor *)malloc(sizeof(t_cursor));
	mlx_get_mouse_pos(master->mlx, &x, &y);
	cursor->x_cur = x;
	cursor->y_cur = y;
	cursor->x_prev = x;
	cursor->y_prev = y;
	return (cursor);
}

int32_t	main(int argc, const char **argv)
{
	t_tab		*map;
	t_map		*vmap;
	mlx_image_t	*img;
	mlx_t		*mlx;
	t_master	*master;

	if (argc == 2)
	{
		map = parse_map(argv[1]);
		if (!map->tab || map->ncols <= 0 || map->nrows <= 0)
		{
			if (map->nrows == -1)
			{
				free(map);
				write(2, "Invalid file\n", 14);
			}
			else if (map->nrows == 0)
			{
				free(map);
				write(2, "Empty file\n", 12);
			}
			else if (map->ncols == -1)
			{
				write(2, "Invalid map column range\n", 26);
				free_tab(*map);
				free(map);
			}
			else
				write(2, "Allocation error\n", 18);
			return (EXIT_FAILURE);
		}
		vmap = tab_to_vect(map);
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
		free_tab(*map);
		free(map);
		free_map(vmap);
		free(master->camera);
		free(master->cursor);
		free(master);
	}
	return (EXIT_SUCCESS);
}
