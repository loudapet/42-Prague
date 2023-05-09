/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:07:29 by plouda            #+#    #+#             */
/*   Updated: 2023/05/09 10:16:30 by plouda           ###   ########.fr       */
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
		print_vectors(dup->vmap, vmap->ncols, row);
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
			vmap->vmap[row][col].x += master->img->width / 2 + camera->x_offset;
			vmap->vmap[row][col].y += master->img->height / 2 + camera->y_offset;
			// No idea?
			vmap->vmap[row][col].y += vmap->ncols * camera->zoom * 2 / 5;
			col++;
		}
		//print_vectors(vmap->vmap, vmap->ncols, row);	
		row++;
	}
	create_raster(master->img, *vmap);
}

void	my_scrollhook(double xdelta, double ydelta, void* param)
{
	t_master	*master;
	t_map	*vmap;

	master = param;
	vmap = master->vmap;
	if (ydelta > 0)
	{
		reset_img(master->img);
		zoom(vmap, 0.1);
		create_raster(master->img, *vmap);
	}
	if (ydelta < 0)
	{
		reset_img(master->img);
		zoom(vmap, -0.1);
		create_raster(master->img, *vmap);
	}
	if (xdelta > 0)
	{
		reset_img(master->img);
		horizontal_shift(vmap, 50);
		create_raster(master->img, *vmap);
	}
	if (xdelta < 0)
	{
		reset_img(master->img);
		horizontal_shift(vmap, -50);
		create_raster(master->img, *vmap);
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_tab	map;
	t_master	*master;
	t_map	*vmap;
	mlx_image_t	*img;

	master = param;
	vmap = master->vmap;
	img = master->img;
	map = master->map;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		horizontal_shift(vmap, 50);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		horizontal_shift(vmap, -50);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		vertical_shift(vmap, -50);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		vertical_shift(vmap, 50);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		///rotate_z(vmap, -1);
		master->camera->gamma += 0.05;
		project(master);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		//rotate_z(vmap, 1);
		master->camera->gamma -= 0.05;
		project(master);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		rotate_y(vmap, -1);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		rotate_y(vmap, 1);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		rotate_x(vmap, 1);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		rotate_x(vmap, -1);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		free_map(vmap);
		vmap = tab_to_vect(&map);
		reset_img(img);
		recenter_vertices(vmap, img);
		rotate_vertices(vmap);
		recenter_vertices(vmap, img);
		scale_vertices(vmap, img);
		recenter_vertices(vmap, img);
		create_raster(img, *vmap);
		master->img = img;
		master->vmap = vmap;
		master->map = map;
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		free_tab(map);
		free_map(vmap);
		mlx_delete_image(master->mlx, img);
		mlx_close_window(master->mlx);
	}
}

void	drag_image(double xpos, double ypos, t_master *master)
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
}

void	my_cursor(double xpos, double ypos, void* param)
{
	t_master	*master;
	t_map	*vmap;

	master = param;
	vmap = master->vmap;
	if (mlx_is_mouse_down(master->mlx, MLX_MOUSE_BUTTON_LEFT) &&
		xpos > 0 && ypos > 0)
	{
		reset_img(master->img);
		drag_image(xpos, ypos, master);
		create_raster(master->img, *vmap);
	}
}

void my_mousehook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_master	*master;
	t_map	*vmap;
	int32_t	xpos;
	int32_t	ypos;

	master = param;
	vmap = master->vmap;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(master->mlx, &xpos, &ypos);
		reset_img(master->img);
		drag_image(xpos, ypos, master);
		create_raster(master->img, *vmap);
	}
	if (!mods)
		return ;
}

t_camera	*init_camera(t_master *master)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->x_offset = 0;
	camera->y_offset = 0;
	if (master->mlx->width / master->vmap->ncols / 2 > master->mlx->height / master->vmap->nrows / 2)
		camera->zoom = master->mlx->height / master->vmap->nrows / 2;
	else
		camera->zoom = master->mlx->width / master->vmap->ncols / 2;
	return (camera);
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
	reset_img(img);
	project(master);
	/* recenter_vertices(vmap, img);
	rotate_vertices(vmap);
	recenter_vertices(vmap, img);
	scale_vertices(vmap, img);
	recenter_vertices(vmap, img); */
	//create_raster(img, *vmap);

	
	mlx_key_hook(mlx, &my_keyhook, master);
	mlx_scroll_hook(mlx, &my_scrollhook, master);
	mlx_mouse_hook(mlx, &my_mousehook, master);
	mlx_cursor_hook(mlx, &my_cursor, master);
	mlx_loop(mlx);

	mlx_terminate(master->mlx);
	free(master);
	return (EXIT_SUCCESS);
}