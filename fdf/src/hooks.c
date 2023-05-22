/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:22:58 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 14:04:58 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	reset_angles(t_camera *camera)
{
	double	tmp;
	double	*angle;

	angle = &tmp;
	tmp = 0;
	if (camera->alpha >= M_PI || camera->alpha <= -M_PI)
		angle = &camera->alpha;
	if (camera->beta >= M_PI || camera->beta <= -M_PI)
		angle = &camera->beta;
	if (camera->gamma >= M_PI || camera->gamma <= -M_PI)
		angle = &camera->gamma;
	if (*angle >= M_PI)
		*angle = deg_to_rad(-179);
	else if (*angle <= -M_PI)
		*angle = deg_to_rad(179);
}

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
		free(master->camera);
		master->camera = init_camera(master);
		project(master);
	}
}
