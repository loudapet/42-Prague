/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_raster.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:52:17 by plouda            #+#    #+#             */
/*   Updated: 2023/05/23 10:25:35 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
Alongside error computation, the function determines whether the unflagged
coordinate should retain its value for the next loop, or increment by 1/-1.
*/
static void	calc_err(t_line *line, int *coord, int delta, int direction)
{
	int	decision;

	if (line->dx > line->dy)
		decision = line->dx;
	else
		decision = line->dy;
	if (line->err > 0)
	{
		*coord += direction;
		line->err -= 2 * decision;
	}
	line->err += 2 * delta;
}

/*
Draws pixels onto the image. The drawing is constricted to the image's
dimensions - if a pixel were to be drawn outside of its dimensions,
the pixel is discarded and the drawing loop continues.

In accordance with the algorithm, the flagged coordinate always increments
by 1/-1.
*/
static void	draw_xy(t_line *line, mlx_image_t *img, char flag)
{
	if (flag == 'x')
	{
		if ((line->cur_x >= 0 && line->cur_y >= 0)
			&& (line->cur_x < (int)img->width
				&& line->cur_y < (int)img->height))
			mlx_put_pixel(img, line->cur_x, line->cur_y, get_clr(*line));
		line->cur_x += line->flag_x;
		calc_err(line, &line->cur_y, line->dy, line->flag_y);
	}
	if (flag == 'y')
	{
		if ((line->cur_x >= 0 && line->cur_y >= 0)
			&& (line->cur_x < (int)img->width
				&& line->cur_y < (int)img->height))
			mlx_put_pixel(img, line->cur_x, line->cur_y, get_clr(*line));
		line->cur_y += line->flag_y;
		calc_err(line, &line->cur_x, line->dx, line->flag_x);
	}
}

/*
Uses Bresenham's algorithm for integer arithmetics line drawing.
*/
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

/*
The conditions prevent runaway lines to the right side and the bottom
of the wireframe.
*/
static void	dispatch_draw(t_map *vmap, mlx_image_t *img, int col, int row)
{
	if (col == vmap->ncols - 1 && row == vmap->nrows - 1)
		return ;
	if (col == vmap->ncols - 1 || row == vmap->nrows - 1)
	{
		if (col == vmap->ncols - 1)
			draw_line(img, vmap->vmap[row][col], vmap->vmap[row + 1][col]);
		if (row == vmap->nrows - 1)
			draw_line(img, vmap->vmap[row][col], vmap->vmap[row][col + 1]);
	}
	else
	{
		draw_line(img, vmap->vmap[row][col], vmap->vmap[row][col + 1]);
		draw_line(img, vmap->vmap[row][col], vmap->vmap[row + 1][col]);
	}
}

/*
As the later functions operate with [row + 1] and [col + 1],
the function only loops through up until the penultimate point.
*/
void	create_raster(mlx_image_t *img, t_map vmap)
{
	int	row;
	int	col;

	row = 0;
	while (row <= vmap.nrows - 1)
	{
		col = 0;
		while (col <= vmap.ncols - 1)
		{
			dispatch_draw(&vmap, img, col, row);
			col++;
		}
		row++;
	}
}
