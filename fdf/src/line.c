/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:53:32 by plouda            #+#    #+#             */
/*   Updated: 2023/05/03 17:30:40 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void calc_direction(t_line *line)
{
	if (line->x2 > line->x1)
		line->flag_x = 1;
	else
		line->flag_x = -1;
	if (line->y2 > line->y1)
		line->flag_y = 1;
	else
		line->flag_y = -1;
}

void calc_err(t_line *line, int *cur_p, int delta, int flag)
{
	int decision;

	if (line->dx > line->dy)
		decision = line->dx;
	else
		decision = line->dy;
	if (line->err > 0)
	{
		*cur_p += flag;
		line->err -= 2 * decision;
	}
	line->err += 2 * delta;
}

t_line init_vars(t_vector p1, t_vector p2)
{
	t_line line;

	line.x1 = (int)p1.x;
	line.x2 = (int)p2.x;
	line.y1 = (int)p1.y;
	line.y2 = (int)p2.y;

	if (abs_val(line.y2 - line.y1) < abs_val(line.x2 - line.x1))
	{
		if (line.x1 > line.x2)
			ft_swap(&line);
	}
	else
	{
		if (line.y1 > line.y2)
			ft_swap(&line);
	}
	line.dx = abs_val(line.x2 - line.x1);
	line.dy = abs_val(line.y2 - line.y1);
	calc_direction(&line);
	line.cur_x = line.x1;
	line.cur_y = line.y1;
	return (line);
}

void draw_line(mlx_image_t *img, t_vector p1, t_vector p2)
{
	t_line line;
	int color;

	color = get_rgba(
		254 % 0xFF, // R
		254 % 0xFF, // G
		254 % 0xFF, // B
		254 % 0xFF	// A
	);
	line = init_vars(p1, p2);
	if (line.dx > line.dy)
	{
		line.err = 2 * line.dy - line.dx;
		while (line.cur_x < line.x2)
		{
			if ((line.cur_x >= 0 && line.cur_y >= 0) && (line.cur_x < (int)img->width && line.cur_y < (int)img->height))
				mlx_put_pixel(img, line.cur_x, line.cur_y, color);
			line.cur_x += line.flag_x;
			calc_err(&line, &line.cur_y, line.dy, line.flag_y);
		}
	}
	else
	{
		line.err = 2 * line.dx - line.dy;
		while (line.cur_y < line.y2)
		{
			if ((line.cur_x >= 0 && line.cur_y >= 0) && (line.cur_x < (int)img->width && line.cur_y < (int)img->height))
				mlx_put_pixel(img, line.cur_x, line.cur_y, color);
			line.cur_y += line.flag_y;
			calc_err(&line, &line.cur_x, line.dx, line.flag_x);
		}
	}
}

void create_raster(mlx_image_t *img, t_map map)
{
	int y;
	int x;

	y = 0;
	while (y <= map.nrows - 1)
	{
		x = 0;
		while (x <= map.ncols - 1)
		{
			if (x == map.ncols - 1 && y == map.nrows - 1)
				break;
			if (x == map.ncols - 1 || y == map.nrows - 1)
			{
				if (x == map.ncols - 1)
					draw_line(img, map.vmap[y][x], map.vmap[y + 1][x]);
				if (y == map.nrows - 1)
					draw_line(img, map.vmap[y][x], map.vmap[y][x + 1]);
			}
			else
			{
				draw_line(img, map.vmap[y][x], map.vmap[y][x + 1]);
				draw_line(img, map.vmap[y][x], map.vmap[y + 1][x]);
			}
			x++;
		}
		y++;
	}
}