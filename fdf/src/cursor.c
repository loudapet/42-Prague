/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:34:50 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 14:13:14 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_cursor(t_cursor *cursor, double xpos, double ypos)
{
	cursor->x_prev = cursor->x_cur;
	cursor->y_prev = cursor->y_cur;
	cursor->x_cur = xpos;
	cursor->y_cur = ypos;
}

static void	translate(t_master *master, double xpos, double ypos)
{
	t_camera	*camera;

	camera = master->camera;
	camera->x_offset += (xpos - master->cursor->x_prev);
	camera->y_offset += (ypos - master->cursor->y_prev);
	project(master);
}

static void	rotate(t_master *master, double xpos, double ypos, int flag)
{
	t_camera	*camera;

	camera = master->camera;
	camera->gamma += (xpos - master->cursor->x_prev) * deg_to_rad(0.2);
	if (flag == BETA)
		camera->beta += (ypos - master->cursor->y_prev) * deg_to_rad(0.2);
	else if (flag == ALPHA)
		camera->alpha += (ypos - master->cursor->y_prev) * deg_to_rad(0.2);
	reset_angles(master->camera);
	project(master);
}

void	cursor(double xpos, double ypos, void *param)
{
	t_master	*master;

	master = param;
	update_cursor(master->cursor, xpos, ypos);
	if (mlx_is_mouse_down(master->mlx, MLX_MOUSE_BUTTON_LEFT))
		translate(master, xpos, ypos);
	if (mlx_is_mouse_down(master->mlx, MLX_MOUSE_BUTTON_RIGHT))
		rotate(master, xpos, ypos, ALPHA);
	if (mlx_is_mouse_down(master->mlx, MLX_MOUSE_BUTTON_MIDDLE))
		rotate(master, xpos, ypos, BETA);
}
