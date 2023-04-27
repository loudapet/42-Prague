/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:09:17 by plouda            #+#    #+#             */
/*   Updated: 2023/04/27 17:49:43 by plouda           ###   ########.fr       */
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

t_limits	get_dimensions(t_map map)
{
	t_limits	limits;

	limits.x_min = min_x(map);
	limits.y_min = min_y(map);
	limits.x_max = max_x(map);
	limits.y_max = max_y(map);
	return(limits);
}

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_tab(t_tab tab)
{
	int	row;

	row = 0;
	while (row < tab.nrows)
	{
		free(tab.tab[row]);
		row++;
	}
	free(tab.tab);
}

void	free_map(t_map map)
{
	int	i;

	i = 0;
	while (i < map.nrows)
	{
		free(map.vmap[i]);
		i++;
	}
	free(map.vmap);
}
