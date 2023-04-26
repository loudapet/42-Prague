/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:27:00 by plouda            #+#    #+#             */
/*   Updated: 2023/04/26 14:13:06 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* From local coordinates to world coordinates, aka from top left corner
of the screen to the middle of the screen */

t_mid	get_midpoint(t_map map)
{
	t_mid	mid;

	mid.mid_x = (max_x(map) + min_x(map)) / 2;
	mid.mid_y = (max_y(map) + min_y(map)) / 2;
	ft_printf("MID X: %d, MID Y: %d\n", mid.mid_x, mid.mid_y);
	return (mid);
}

void	translate_vertices(t_map *map, mlx_image_t *img)
{
	t_mid	mid;
	int		row;
	int		col;

	mid = get_midpoint(*map);
	row = 0;
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			map->vmap[row][col].x += (img->width / 2) - mid.mid_x;
			map->vmap[row][col].y += (img->height / 2) - mid.mid_y;
			col++;
		}
		print_vectors(map->vmap, map->ncols, row);
		row++;
	}
}

void	scale_vertices(t_map *map, mlx_image_t *img)
{
	int	row;
	int	col;
	t_limits	limits;
	float	scale_x;
	float	scale_y;

	if (img)
		limits = get_dimensions(*map);
	row = 0;
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			map->vmap[row][col].x -= limits.x_min;
			map->vmap[row][col].y -= limits.y_min;
			col++;
		}
		ft_printf("AFTER ORIGIN 0,0 RESET\n");
		print_vectors(map->vmap, map->ncols, row);
		row++;
	}
	limits = get_dimensions(*map);
	scale_x = ((float)img->width  / limits.x_max) * 0.9;
	scale_y = ((float)img->height / limits.y_max) * 0.9;
	printf("SCALE X: %f, SCALE Y: %f\n", scale_x, scale_y);
	row = 0;
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			map->vmap[row][col].x = (float)map->vmap[row][col].x * scale_x;
			map->vmap[row][col].y = (float)map->vmap[row][col].y * scale_y;
			col++;
		}
		ft_printf("AFTER SCALING\n");
		print_vectors(map->vmap, map->ncols, row);
		row++;
	}
}

/* 45 deg along y-axis, then 45 deg along x-axis.
Thought process: z-component isn't actually a proper z-component, we only work with
2D vectors in reality (or rather, it's the same for every vector, and we ignore it).
Therefore, we only use those parts of the rotation matrix that concern x- and y-components,
and since the x-component when rotating around x-axis is 0, and the same goes for y-component
and y-axis, the only thing left is cos(theta).
The gap: https://clintbellanger.net/articles/isometric_math/. (why is cos(0.8) and sin(0.8)
the same as TILE_HEIGHT and TILE_WIDTH?)
We subtract 'z' from y to simulate altitude.
 */
void	rotate_vertices(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			map->vmap[row][col].x = (float)(map->vmap[row][col].x - map->vmap[row][col].y) * cos(0.8);
			map->vmap[row][col].y = (float)(map->vmap[row][col].x + map->vmap[row][col].y) * sin(0.8) - (float)map->vmap[row][col].z;
			col++;
		}
		row++;
	}
}

void	recenter_map(t_map *map)
{	
	int	row;
	int	col;
	int	x_off;
	int	y_off;

	x_off = min_x(*map);
	y_off = min_y(*map);
	row = 0;
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			map->vmap[row][col].x -= x_off;
			map->vmap[row][col].y -= y_off;
			col++;
		}
		//print_vectors(map->vmap, map->ncols, row);
		row++;
	}
}