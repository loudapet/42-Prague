/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:09:17 by plouda            #+#    #+#             */
/*   Updated: 2023/05/14 16:37:16 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	rad_to_deg(double rad)
{
	double	deg;

	deg = rad * 180/M_PI;
	return (deg);
}

double	deg_to_rad(double deg)
{
	double	rad;

	rad = deg * M_PI/180;
	return (rad);
}

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
	tmp = line->color1;
	line->color1 = line->color2;
	line->color2 = tmp;
}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	reset_img(mlx_image_t *img)
{
	int	color;
	u_int32_t	x;
	u_int32_t	y;

	color = 0x000000ff;
	x = 0;
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
	x = 0;
	while (x < 300)
	{
		color = 0x202020ff;
		if (x == 299)
			color = 0xffffffff;
		y = 0;
		while (y < 160)
		{
			if (y == 159)
				color = 0xffffffff;
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
}