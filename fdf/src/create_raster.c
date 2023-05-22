/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_raster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:52:17 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 14:53:21 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_xy(t_line *line, mlx_image_t *img, char flag)
{
	if (flag == 'x')
	{
		if ((line->cur_x >= 0 && line->cur_y >= 0) && \
			(line->cur_x < (int)img->width && line->cur_y < (int)img->height))
			mlx_put_pixel(img, line->cur_x, line->cur_y, get_clr(*line));
		line->cur_x += line->flag_x;
		calc_err(line, &line->cur_y, line->dy, line->flag_y);
	}
	if (flag == 'y')
	{
		if ((line->cur_x >= 0 && line->cur_y >= 0) && \
			(line->cur_x < (int)img->width && line->cur_y < (int)img->height))
			mlx_put_pixel(img, line->cur_x, line->cur_y, get_clr(*line));
		line->cur_y += line->flag_y;
		calc_err(line, &line->cur_x, line->dx, line->flag_x);
	}
}

static void	draw_line(mlx_image_t *img, t_vector p1, t_vector p2)
{
	t_line	line;

	line = init_vars(p1, p2);
	if (line.dx > line.dy)
	{
		line.err = 2 * line.dy - line.dx;
		while (line.cur_x < line.x2)
			draw_xy(&line, img, 'x');
	}
	else
	{
		line.err = 2 * line.dx - line.dy;
		while (line.cur_y < line.y2)
			draw_xy(&line, img, 'y');
	}
}

static void	dispatch_draw(t_map *vmap, mlx_image_t *img, int x, int y)
{
	if (x == vmap->ncols - 1 || y == vmap->nrows - 1)
	{
		if (x == vmap->ncols - 1)
			draw_line(img, vmap->vmap[y][x], vmap->vmap[y + 1][x]);
		if (y == vmap->nrows - 1)
			draw_line(img, vmap->vmap[y][x], vmap->vmap[y][x + 1]);
	}
	else
	{
		draw_line(img, vmap->vmap[y][x], vmap->vmap[y][x + 1]);
		draw_line(img, vmap->vmap[y][x], vmap->vmap[y + 1][x]);
	}
}

void	create_raster(mlx_image_t *img, t_map map)
{
	int	y;
	int	x;

	y = 0;
	while (y <= map.nrows - 1)
	{
		x = 0;
		while (x <= map.ncols - 1)
		{
			if (x == map.ncols - 1 && y == map.nrows - 1)
				break ;
			dispatch_draw(&map, img, x, y);
			x++;
		}
		y++;
	}
}
