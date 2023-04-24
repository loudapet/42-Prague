/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:09:17 by plouda            #+#    #+#             */
/*   Updated: 2023/04/24 18:28:08 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	abs_val(int nb)
{
	if (nb < 0)
		nb = -nb;
	return (nb);
}

void	ft_swap(t_line *line)
{
	int	tmp;

	tmp = line->x1;
	line->x1 = line->x2;
	line->x2 = tmp;
	tmp = line->y1;
	line->y1 = line->y2;
	line->y2 = tmp;
}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	min_x(t_map map)
{
	int	min;
	int y;
	int x;
	int	xcoor;

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
	ft_printf("MINIMUM X VAL: %d \n", min);
	return (min);
}

int	min_y(t_map map)
{
	int	min;
	int y;
	int x;
	int	ycoor;

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
	ft_printf("MINIMUM Y VAL: %d \n", min);
	return (min);
}

int	max_x(t_map map)
{
	int	max;
	int y;
	int x;
	int	xcoor;

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
	ft_printf("MAXIMUM X VAL: %d \n", max);
	return (max);
}

int	max_y(t_map map)
{
	int	max;
	int y;
	int x;
	int	ycoor;

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
	ft_printf("MAXIMUM Y VAL: %d \n", max);
	return (max);
}

int	min_val(t_map map)
{
	int	min;
	int y;
	int x;
	int	xcoor;
	int	ycoor;
	int	zcoor;
	int	xprime;
	int	yprime;

	min = 0;
	y = 0;
	while (y < map.nrows)
	{
		x = 0;
		while (x < map.ncols)
		{
			xcoor = map.vmap[y][x].x;
			ycoor = map.vmap[y][x].y;
			zcoor = map.vmap[y][x].z;
			xprime = (xcoor - ycoor) * cos(0.8);
			yprime = (xcoor + ycoor) * sin(0.8) - zcoor;
			if (xprime < min)
				min = xprime;
			if (yprime < min)
				min = yprime;
			x++;
		}
		y++;
	}
	ft_printf("MINIMUM VAL: %d \n", min);
	return (min);
}

int	max_val(t_map map)
{
	int	max;
	int y;
	int x;
	int	xcoor;
	int	ycoor;
	int	zcoor;
	int	xprime;
	int	yprime;

	max = 0;
	y = 0;
	while (y < map.nrows)
	{
		x = 0;
		while (x < map.ncols)
		{
			xcoor = map.vmap[y][x].x;
			ycoor = map.vmap[y][x].y;
			zcoor = map.vmap[y][x].z;
			xprime = (xcoor - ycoor) * cos(0.8);
			yprime = (xcoor + ycoor) * sin(0.8) - zcoor;
			if (xprime > max)
				max = xprime;
			if (yprime > max)
				max = yprime;
			x++;
		}
		y++;
	}
	ft_printf("MAXIMUM VAL: %d \n", max);
	return (max);
}