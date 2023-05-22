/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:09:17 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 17:43:21 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	line_swap(t_line *line)
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

static void	fill_black(mlx_image_t *img)
{
	int			color;
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
}

static void	fill_instructions(mlx_image_t *img)
{
	int			color;
	u_int32_t	x;
	u_int32_t	y;

	x = 0;
	while (x < 230)
	{
		color = 0x202020ff;
		if (x == 229)
			color = 0xffffffff;
		y = 0;
		while (y < 325)
		{
			if (y == 324)
				color = 0xffffffff;
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
}

void	reset_img(mlx_image_t *img)
{
	fill_black(img);
	fill_instructions(img);
}

void	error(void)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}