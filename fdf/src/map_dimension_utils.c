/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dimension_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:59:32 by plouda            #+#    #+#             */
/*   Updated: 2023/04/27 18:44:15 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	min_x(t_map map)
{
	float	min;
	int y;
	int x;
	float	xcoor;

	min = map.vmap[0][0].x;
	y = 0;
	while (y < map.nrows)
	{
		x = 0;
		while (x < map.ncols)
		{
			xcoor = map.vmap[y][x].x;
			if (xcoor < min)
				min = xcoor;
			x++;
		}
		y++;
	}
	printf("MINIMUM X VAL: %f \n", min);
	return (min);
}

float	min_y(t_map map)
{
	float	min;
	int y;
	int x;
	float	ycoor;

	min = map.vmap[0][0].y;
	y = 0;
	while (y < map.nrows)
	{
		x = 0;
		while (x < map.ncols)
		{
			ycoor = map.vmap[y][x].y;
			if (ycoor < min)
				min = ycoor;
			x++;
		}
		y++;
	}
	printf("MINIMUM Y VAL: %f \n", min);
	return (min);
}

float	max_x(t_map map)
{
	float	max;
	int y;
	int x;
	float	xcoor;

	max = map.vmap[0][0].x;
	y = 0;
	while (y < map.nrows)
	{
		x = 0;
		while (x < map.ncols)
		{
			xcoor = map.vmap[y][x].x;
			if (xcoor > max)
				max = xcoor;
			x++;
		}
		y++;
	}
	printf("MAXIMUM X VAL: %f \n", max);
	return (max);
}

float	max_y(t_map map)
{
	float	max;
	int y;
	int x;
	float	ycoor;

	max = map.vmap[0][0].y;
	y = 0;
	while (y < map.nrows)
	{
		x = 0;
		while (x < map.ncols)
		{
			ycoor = map.vmap[y][x].y;
			if (ycoor > max)
				max = ycoor;
			x++;
		}
		y++;
	}
	printf("MAXIMUM Y VAL: %f \n", max);
	return (max);
}

float	max_z(t_map map)
{
	float	max;
	int y;
	int x;
	float	zcoor;

	max = map.vmap[0][0].z;
	y = 0;
	while (y < map.nrows)
	{
		x = 0;
		while (x < map.ncols)
		{
			zcoor = map.vmap[y][x].z;
			if (zcoor > max)
				max = zcoor;
			x++;
		}
		y++;
	}
	printf("MAXIMUM Z VAL: %f \n", max);
	return (max);
}

t_limits	get_dimensions(t_map map)
{
	t_limits	limits;

	limits.x_min = min_x(map);
	limits.y_min = min_y(map);
	limits.x_max = max_x(map);
	limits.y_max = max_y(map);
	limits.z_max = max_z(map);
	return(limits);
}
