/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:22:58 by plouda            #+#    #+#             */
/*   Updated: 2023/05/15 09:39:20 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	ft_reset_angles(double angle)
{
	if (angle >= M_PI)
		return (-2 * M_PI - angle);
	else if (angle <= -M_PI)
		return (2 * M_PI + angle);
	return (angle);
}

void	cursor(double xpos, double ypos, void* param)
{
	t_master	*master;

	master = param;
	master->cursor->x_prev = master->cursor->x_cur;
	master->cursor->y_prev = master->cursor->y_cur;
	master->cursor->x_cur = xpos;
	master->cursor->y_cur = ypos;
	if (mlx_is_mouse_down(master->mlx, MLX_MOUSE_BUTTON_LEFT) &&
		xpos > 0 && ypos > 0)
	{
		master->camera->x_offset += (xpos - master->cursor->x_prev);
		master->camera->y_offset += (ypos - master->cursor->y_prev);
		project(master);
	}
	if (mlx_is_mouse_down(master->mlx, MLX_MOUSE_BUTTON_RIGHT) &&
		xpos > 0 && ypos > 0)
	{
		master->camera->gamma += (xpos - master->cursor->x_prev) * 0.005;
		master->camera->alpha += (ypos - master->cursor->y_prev) * 0.005;
		master->camera->gamma = ft_reset_angles(master->camera->gamma);
		master->camera->alpha = ft_reset_angles(master->camera->alpha);
		project(master);
	}
}

void	scrollhook(double xdelta, double ydelta, void* param)
{
	t_master	*master;
	//t_map	*vmap;

	master = param;
	//vmap = master->vmap;
	if (ydelta > 0)
	{
		master->camera->zoom -= 1.;
		if (master->camera->zoom < 1.)
			master->camera->zoom = 1.;
		project(master);
	}
	if (ydelta < 0)
	{
		master->camera->zoom += 1.;
		project(master);
	}
	if (xdelta > 0)
	{
		master->camera->x_offset += 25;
		project(master);
	}
	if (xdelta < 0)
	{
		master->camera->x_offset -= 25;
		project(master);
	}
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	//t_tab	map;
	t_master	*master;
	//t_map	*vmap;
	//mlx_image_t	*img;

	master = param;
	//vmap = master->vmap;
	//img = master->img;
	//map = master->map;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->x_offset += 25;
		project(master);
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->x_offset -= 25;
		project(master);
	}
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->y_offset -= 25;
		project(master);
	}
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->y_offset += 25;
		project(master);
	}
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->gamma -= 0.05;
		printf("alpha: %f, beta: %f, gamma: %f\n", master->camera->alpha * 180/M_PI, master->camera->beta * 180/M_PI, master->camera->gamma * 180/M_PI);
		project(master);
	}
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->gamma += 0.05;
		printf("alpha: %f, beta: %f, gamma: %f\n", master->camera->alpha * 180/M_PI, master->camera->beta * 180/M_PI, master->camera->gamma * 180/M_PI);
		project(master);
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->beta -= 0.05;
		printf("alpha: %f, beta: %f, gamma: %f\n", master->camera->alpha * 180/M_PI, master->camera->beta * 180/M_PI, master->camera->gamma * 180/M_PI);
		project(master);
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->beta += 0.05;
		printf("alpha: %f, beta: %f, gamma: %f\n", master->camera->alpha * 180/M_PI, master->camera->beta * 180/M_PI, master->camera->gamma * 180/M_PI);
		project(master);
	}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->alpha -= 0.05;
		printf("alpha: %f, beta: %f, gamma: %f\n", master->camera->alpha * 180/M_PI, master->camera->beta * 180/M_PI, master->camera->gamma * 180/M_PI);
		project(master);
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->alpha += 0.05;
		printf("alpha: %f, beta: %f, gamma: %f\n", master->camera->alpha * 180/M_PI, master->camera->beta * 180/M_PI, master->camera->gamma * 180/M_PI);
		project(master);
	}
	if (keydata.key == MLX_KEY_Z && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->z_div += 0.1;
		project(master);
	}
	if (keydata.key == MLX_KEY_X && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->z_div -= 0.1;
		if (master->camera->z_div <= 0.1)
			master->camera->z_div = 0.1;
		project(master);
	}
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
	{
		master->camera->x_offset = 0;
		master->camera->y_offset = 0;
		project(master);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		free(master->camera);
		master->camera = init_camera(master);
		project(master);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(master->mlx);
}