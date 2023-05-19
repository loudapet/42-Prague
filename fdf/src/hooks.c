/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:22:58 by plouda            #+#    #+#             */
/*   Updated: 2023/05/19 20:19:15 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	reset_angles(t_camera *camera)
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

void	cursor(double xpos, double ypos, void *param)
{
	t_master	*master;
	int			flag;

	flag = 0;
	master = param;
	master->cursor->x_prev = master->cursor->x_cur;
	master->cursor->y_prev = master->cursor->y_cur;
	master->cursor->x_cur = xpos;
	master->cursor->y_cur = ypos;
	if (mlx_is_mouse_down(master->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& xpos > 0 && ypos > 0)
	{
		master->camera->x_offset += (xpos - master->cursor->x_prev);
		master->camera->y_offset += (ypos - master->cursor->y_prev);
		project(master);
	}
	if (mlx_is_mouse_down(master->mlx, MLX_MOUSE_BUTTON_RIGHT)
		&& xpos > 0 && ypos > 0)
	{
		master->camera->gamma += (xpos - master->cursor->x_prev) * deg_to_rad(0.2);
		master->camera->alpha += (ypos - master->cursor->y_prev) * deg_to_rad(0.2);
		flag++;
	}
	if (mlx_is_mouse_down(master->mlx, MLX_MOUSE_BUTTON_MIDDLE)
		&& xpos > 0 && ypos > 0)
	{
		master->camera->gamma += (xpos - master->cursor->x_prev) * deg_to_rad(0.2);
		master->camera->beta += (ypos - master->cursor->y_prev) * deg_to_rad(0.2);
		flag++;
	}
	if (flag)
	{
		reset_angles(master->camera);
		project(master);
	}
}

void	scrollhook(double xdelta, double ydelta, void *param)
{
	t_master	*master;

	master = param;
	if (ydelta > 0)
	{
		master->camera->zoom += 1.;
		project(master);
	}
	if (ydelta < 0)
	{
		master->camera->zoom -= 1.;
		if (master->camera->zoom < 1.)
			master->camera->zoom = 1.;
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
	t_master	*master;
	int			flag;

	flag = 0;
	master = param;
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
		master->camera->gamma -= deg_to_rad(1);
		flag++;
	}
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->gamma += deg_to_rad(1);
		flag++;
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->beta -= deg_to_rad(1);
		flag++;
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->beta += deg_to_rad(1);
		flag++;
	}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->alpha -= deg_to_rad(1);
		flag++;
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->alpha += deg_to_rad(1);
		flag++;
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
	if (keydata.key == MLX_KEY_C && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->vmap->clr_flag--;
		if (master->vmap->clr_flag < -3)
			master->vmap->clr_flag = -1;
		project(master);
	}
	if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
	{
		master->camera->x_offset = 0;
		master->camera->y_offset = 0;
		project(master);
	}
	if (keydata.key == MLX_KEY_P && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		master->camera->projection++;
		if (master->camera->projection > CAV)
			master->camera->projection = ISO;
		project(master);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		free(master->camera);
		master->camera = init_camera(master);
		master->vmap->clr_flag = DEFAULT;
		project(master);
	}
	if (flag)
	{
		reset_angles(master->camera);
		project(master);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(master->mlx);
}
