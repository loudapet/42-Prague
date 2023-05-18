/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:53:32 by plouda            #+#    #+#             */
/*   Updated: 2023/05/18 19:12:29 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	get_ratio(int start, int finish, int cur)
{
	double	ratio;

	if (start == finish)
		return (1.0);
	ratio = (double)(cur - start) / (finish - start);
	return (ratio);
}

int	get_default_clr(int z, float min_z, float max_z, int flag)
{
	double	ratio;

	//printf("MIN Z: %f, MAX Z: %f\n", min_z, max_z);
	ratio = get_ratio(min_z, max_z, z);
	//printf("Ratio: %f\n", ratio);
	
	if (flag == DEFAULT)
		return (0xffffffff);
	if (flag == TOPO)
		return (topo_palette(ratio));
	if (flag == RAINBOW)
		return (rainbow_palette(ratio));
	return (0x00000000);
}

static int	do_lerp(int start, int finish, double ratio)
{
	return ((int)start + ratio * (finish - start));
}

/*
** Quadrant 1, 4, 5, 8(delta.x > delta.y): sample by x
** Quadrant 2, 3, 6, 7(delta.x < delta.y): sample by y

In a nutshell, “& 0xff” effectively masks the variable so it leaves 
only the value in the last 8 bits, and ignores all the rest of the bits.
*/

int	get_clr(t_line line)
{
	double	ratio;
	int		red;
	int		green;
	int		blue;
	int		alpha;

	if (line.dx > line.dy)
		ratio = get_ratio(line.x1, line.x2, line.cur_x);
	else
		ratio = get_ratio(line.y1, line.y2, line.cur_y);
	red = do_lerp((line.color1 >> 24) & 0xFF, (line.color2 >> 24) & 0xFF, ratio);
	green = do_lerp((line.color1 >> 16) & 0xFF, (line.color2 >> 16) & 0xFF, ratio);
	blue = do_lerp(line.color1 >> 8 & 0xFF, line.color2 >> 8 & 0xFF, ratio);
	alpha = 255;
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

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
	line.dx = abs_val(line.x2 - line.x1);
	line.dy = abs_val(line.y2 - line.y1);
	line.color1 = p1.color;
	line.color2 = p2.color;
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
	calc_direction(&line);
	line.cur_x = line.x1;
	line.cur_y = line.y1;
	return (line);
}

void draw_line(mlx_image_t *img, t_vector p1, t_vector p2)
{
	t_line line;

	line = init_vars(p1, p2);
	if (line.dx > line.dy)
	{
		line.err = 2 * line.dy - line.dx;
		while (line.cur_x < line.x2)
		{
			if ((line.cur_x >= 0 && line.cur_y >= 0) && (line.cur_x < (int)img->width && line.cur_y < (int)img->height))
				mlx_put_pixel(img, line.cur_x, line.cur_y, get_clr(line));
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
				mlx_put_pixel(img, line.cur_x, line.cur_y, get_clr(line));
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