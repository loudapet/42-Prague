/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:22:58 by plouda            #+#    #+#             */
/*   Updated: 2023/05/09 11:25:32 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* void	cursor(double xpos, double ypos, void* param)
{
	t_master	*master;
	t_map	*vmap;

	master = param;
	vmap = master->vmap;
	if (mlx_is_mouse_down(master->mlx, MLX_MOUSE_BUTTON_LEFT) &&
		xpos > 0 && ypos > 0)
	{
		reset_img(master->img);
		drag_image(xpos, ypos, master);
		create_raster(master->img, *vmap);
	}
}

void mousehook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_master	*master;
	t_map	*vmap;
	int32_t	xpos;
	int32_t	ypos;

	master = param;
	vmap = master->vmap;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(master->mlx, &xpos, &ypos);
		reset_img(master->img);
		drag_image(xpos, ypos, master);
		create_raster(master->img, *vmap);
	}
	if (!mods)
		return ;
} */

void	scrollhook(double xdelta, double ydelta, void* param)
{
	t_master	*master;
	//t_map	*vmap;

	master = param;
	//vmap = master->vmap;
	if (ydelta > 0)
	{
		reset_img(master->img);
		master->camera->zoom += 1;
		project(master);
	}
	if (ydelta < 0)
	{
		reset_img(master->img);
		master->camera->zoom -= 1;
		project(master);
	}
	if (xdelta > 0)
	{
		reset_img(master->img);
		master->camera->x_offset += 25;
		project(master);
	}
	if (xdelta < 0)
	{
		reset_img(master->img);
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
		reset_img(master->img);
		master->camera->x_offset += 25;
		project(master);
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		master->camera->x_offset -= 25;
		project(master);
	}
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		master->camera->y_offset -= 25;
		project(master);
	}
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		master->camera->y_offset += 25;
		project(master);
	}
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		master->camera->gamma -= 0.05;
		project(master);
	}
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		master->camera->gamma += 0.05;
		project(master);
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		master->camera->beta -= 0.05;
		project(master);
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		master->camera->beta += 0.05;
		project(master);
	}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		master->camera->alpha -= 0.05;
		project(master);
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		master->camera->alpha += 0.05;
		project(master);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		reset_img(master->img);
		free(master->camera);
		master->camera = init_camera(master);
		project(master);
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(master->mlx);
}