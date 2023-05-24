/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:22:58 by plouda            #+#    #+#             */
/*   Updated: 2023/05/23 11:09:20 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	resizehook(int32_t width, int32_t height, void *param)
{
	t_master	*master;
	uint32_t	new_width;
	uint32_t	new_height;

	master = param;
	new_width = (uint32_t)width;
	new_height = (uint32_t)height;
	if (master->img->width != new_width || master->img->height != new_height)
	{
		mlx_resize_image(master->img, width, height);
		project(master);
	}
}
