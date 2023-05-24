/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:47:22 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 14:07:48 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translate(t_master *master, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_RIGHT)
		master->camera->x_offset += 25;
	if (keydata.key == MLX_KEY_LEFT)
		master->camera->x_offset -= 25;
	if (keydata.key == MLX_KEY_UP)
		master->camera->y_offset -= 25;
	if (keydata.key == MLX_KEY_DOWN)
		master->camera->y_offset += 25;
	project(master);
}

static void	rotate(t_master *master, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_Q)
		master->camera->gamma -= deg_to_rad(1);
	if (keydata.key == MLX_KEY_E)
		master->camera->gamma += deg_to_rad(1);
	if (keydata.key == MLX_KEY_A)
		master->camera->beta -= deg_to_rad(1);
	if (keydata.key == MLX_KEY_D)
		master->camera->beta += deg_to_rad(1);
	if (keydata.key == MLX_KEY_W)
		master->camera->alpha -= deg_to_rad(1);
	if (keydata.key == MLX_KEY_S)
		master->camera->alpha += deg_to_rad(1);
	reset_angles(master->camera);
	project(master);
}

static void	special_key_events(t_master *master, mlx_key_data_t keydata)
{
	if ((keydata.key == MLX_KEY_Z
			|| keydata.key == MLX_KEY_X)
		&& keydata.action != MLX_RELEASE)
		flatten(master, keydata);
	if ((keydata.key == MLX_KEY_C)
		&& keydata.action != MLX_RELEASE)
		change_color(master);
	if ((keydata.key == MLX_KEY_P)
		&& keydata.action != MLX_RELEASE)
		change_projection(master);
	if ((keydata.key == MLX_KEY_T)
		&& keydata.action != MLX_RELEASE)
		recenter_camera(master);
	if ((keydata.key == MLX_KEY_R)
		&& keydata.action != MLX_RELEASE)
		reset(master);
	if ((keydata.key == MLX_KEY_ESCAPE)
		&& keydata.action == MLX_PRESS)
		mlx_close_window(master->mlx);
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_master	*master;

	master = param;
	if ((keydata.key == MLX_KEY_RIGHT
			|| keydata.key == MLX_KEY_LEFT
			|| keydata.key == MLX_KEY_UP
			|| keydata.key == MLX_KEY_DOWN)
		&& keydata.action != MLX_RELEASE)
		translate(master, keydata);
	if ((keydata.key == MLX_KEY_Q
			|| keydata.key == MLX_KEY_E
			|| keydata.key == MLX_KEY_A
			|| keydata.key == MLX_KEY_D
			|| keydata.key == MLX_KEY_W
			|| keydata.key == MLX_KEY_S)
		&& keydata.action != MLX_RELEASE)
		rotate(master, keydata);
	special_key_events(master, keydata);
}
