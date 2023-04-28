/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:24:53 by plouda            #+#    #+#             */
/*   Updated: 2023/04/28 16:21:41 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	horizontal_shift(t_map *map, int amount)
{
	int		row;
	int		col;

	row = 0;
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			map->vmap[row][col].x += amount;
			col++;
		}
		row++;
	}
}

void	vertical_shift(t_map *map, int amount)
{
	int		row;
	int		col;

	row = 0;
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			map->vmap[row][col].y += amount;
			col++;
		}
		row++;
	}
}

void	zoom(t_map *map, float amount)
{
	int	row;
	int	col;
	t_mid	mid;

	mid = get_midpoint(*map);
	row = 0;
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			map->vmap[row][col].x = map->vmap[row][col].x - mid.mid_x;
			map->vmap[row][col].y = map->vmap[row][col].y - mid.mid_y;
			map->vmap[row][col].x = map->vmap[row][col].x * (1 + amount) + mid.mid_x;
			map->vmap[row][col].y = map->vmap[row][col].y * (1 + amount) + mid.mid_y;
			col++;
		}
		row++;
	}
	
}