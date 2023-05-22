/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:40:52 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 14:02:43 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	flatten(t_master *master, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_Z)
		master->camera->z_div += 0.1;
	if (keydata.key == MLX_KEY_X)
	{
		master->camera->z_div -= 0.1;
		if (master->camera->z_div <= 0.1)
			master->camera->z_div = 0.1;
	}
	project(master);
}

void	change_color(t_master *master)
{
	master->vmap->clr_flag--;
	if (master->vmap->clr_flag < -3)
		master->vmap->clr_flag = -1;
	project(master);
}

void	change_projection(t_master *master)
{
	master->camera->projection++;
	if (master->camera->projection > CAV)
		master->camera->projection = ISO;
	project(master);
}

void	recenter_camera(t_master *master)
{
	master->camera->x_offset = 0;
	master->camera->y_offset = 0;
	project(master);
}

void	reset(t_master *master)
{
	free(master->camera);
	master->camera = init_camera(master);
	master->vmap->clr_flag = DEFAULT;
	project(master);
}
