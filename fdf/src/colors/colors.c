/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:53:32 by plouda            #+#    #+#             */
/*   Updated: 2023/05/24 11:33:22 by plouda           ###   ########.fr       */
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

static int	do_lerp(int start, int finish, double ratio)
{
	return ((int)start + ratio * (finish - start));
}

/*
Computes the color of every pixel using linear interpolation.

Note: “& 0xff” effectively masks the variable so it leaves 
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
	red = do_lerp((line.color1 >> 24) & 0xFF, \
			(line.color2 >> 24) & 0xFF, ratio);
	green = do_lerp((line.color1 >> 16) & 0xFF, \
			(line.color2 >> 16) & 0xFF, ratio);
	blue = do_lerp(line.color1 >> 8 & 0xFF, \
			line.color2 >> 8 & 0xFF, ratio);
	alpha = 255;
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

int	get_default_clr(int z, int min_z, int max_z, int flag)
{
	double	ratio;

	ratio = get_ratio(min_z, max_z, z);
	if (flag == DEFAULT)
		return (0xffffffff);
	if (flag == TOPO)
		return (topo_palette(ratio));
	if (flag == RAINBOW)
		return (rainbow_palette(ratio));
	if (flag == SUNRISE)
		return (sunrise_palette(ratio));
	return (0x00000000);
}
