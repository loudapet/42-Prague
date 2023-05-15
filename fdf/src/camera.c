/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:59:30 by plouda            #+#    #+#             */
/*   Updated: 2023/05/15 14:38:19 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_camera	*init_camera(t_master *master)
{
	t_camera	*camera;

	camera = (t_camera *)malloc(sizeof(t_camera));
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->x_offset = 0;
	camera->y_offset = 0;
	camera->z_div = 1;
	camera->projection = ISO;
	if (master->mlx->width / master->vmap->ncols / 2 > master->mlx->height / master->vmap->nrows / 2)
		camera->zoom = (double)(master->mlx->height / master->vmap->nrows / 2);
	else
		camera->zoom = (double)(master->mlx->width / master->vmap->ncols / 2);
	if (camera->zoom < 1)
		camera->zoom = 1;
	return (camera);
}