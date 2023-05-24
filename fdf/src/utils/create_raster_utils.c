/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_raster_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:53:48 by plouda            #+#    #+#             */
/*   Updated: 2023/05/23 09:38:35 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	line_swap(t_line *line)
{
	int	tmp;

	tmp = line->x1;
	line->x1 = line->x2;
	line->x2 = tmp;
	tmp = line->y1;
	line->y1 = line->y2;
	line->y2 = tmp;
	tmp = line->color1;
	line->color1 = line->color2;
	line->color2 = tmp;
}

static void	calc_direction(t_line *line)
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

/*
Line swap is occasionally performed because the algorithm
can only handle "bottom left-top right" drawing in its default form.

The decision variable (dx/dy) doesn't change after this point,
so its value determines the path the algorithm takes for its
further computations.
*/
t_line	init_vars(t_vector p1, t_vector p2)
{
	t_line	line;

	line.x1 = (int)p1.x;
	line.x2 = (int)p2.x;
	line.y1 = (int)p1.y;
	line.y2 = (int)p2.y;
	line.dx = abs_val(line.x2 - line.x1);
	line.dy = abs_val(line.y2 - line.y1);
	line.color1 = p1.color;
	line.color2 = p2.color;
	if (line.dx > line.dy)
	{
		if (line.x1 > line.x2)
			line_swap(&line);
	}
	else
	{
		if (line.y1 > line.y2)
			line_swap(&line);
	}
	calc_direction(&line);
	line.cur_x = line.x1;
	line.cur_y = line.y1;
	return (line);
}
