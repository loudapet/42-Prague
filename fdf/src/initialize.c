/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:59:30 by plouda            #+#    #+#             */
/*   Updated: 2023/05/24 08:41:07 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_camera	*init_camera(t_master *master)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->x_offset = 0;
	camera->y_offset = 0;
	camera->z_div = 1;
	camera->projection = ISO;
	if (master->mlx->width / master->vmap->ncols / 2 > \
		master->mlx->height / master->vmap->nrows / 2)
		camera->zoom = (double)(master->mlx->height / \
		master->vmap->nrows / 2);
	else
		camera->zoom = (double)(master->mlx->width / \
		master->vmap->ncols / 2);
	if (camera->zoom < 1)
		camera->zoom = 1;
	return (camera);
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

t_tab	*init_tab(const char *path)
{
	t_tab	*map;

	map = malloc(sizeof(t_tab));
	map->nrows = row_count(path);
	map->ncols = 0;
	map->map_fd = open(path, O_RDONLY);
	if (map->map_fd < 0)
		map->nrows = -1;
	if (map->nrows <= 0)
		return (map);
	map->tab = malloc(2 * sizeof(int **));
	map->tab[0] = malloc(map->nrows * sizeof(int *));
	map->tab[1] = malloc(map->nrows * sizeof(int *));
	map->validation[0] = -1;
	map->validation[1] = -1;
	if (!map->tab[0] || !map->tab[1] || !map->tab)
	{
		map->tab = NULL;
		return (map);
	}
	return (map);
}

mlx_image_t	*init_img(mlx_t *mlx)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, mlx->width, mlx->height);
	if (!img)
		error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		error();
	return (img);
}

t_master	*init_master(mlx_t *mlx, mlx_image_t *img, t_tab *map, t_map *vmap)
{
	t_master	*master;

	master = malloc(sizeof(t_master));
	if (!master)
	{
		master = NULL;
		return (master);
	}
	master->mlx = mlx;
	master->img = img;
	master->vmap = vmap;
	master->map = map;
	master->camera = init_camera(master);
	master->cursor = init_cursor(master);
	return (master);
}
