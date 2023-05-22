/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:12:06 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 14:13:34 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	scale_and_zoom(t_map *dup, t_camera *camera, int row, int col)
{
	dup->vmap[row][col].x *= camera->zoom;
	dup->vmap[row][col].y *= camera->zoom;
	dup->vmap[row][col].z *= camera->zoom / camera->z_div;
}

void	shift_to_origin(t_map *dup, t_camera *camera, int row, int col)
{
	dup->vmap[row][col].x -= dup->ncols * camera->zoom / 2;
	dup->vmap[row][col].y -= dup->nrows * camera->zoom / 2;
}

void	rotate_xyz(t_map *dup, t_camera *camera, int row, int col)
{
	rot_x(&dup->vmap[row][col].y, &dup->vmap[row][col].z, camera->alpha);
	rot_y(&dup->vmap[row][col].x, &dup->vmap[row][col].z, camera->beta);
	rot_z(&dup->vmap[row][col].x, &dup->vmap[row][col].y, camera->gamma);
}

void	convert_projection(t_map *dup, t_camera *camera, int row, int col)
{
	float	*x;
	float	*y;
	float	*z;

	x = &dup->vmap[row][col].x;
	y = &dup->vmap[row][col].y;
	z = &dup->vmap[row][col].z;
	if (camera->projection == ISO)
		conv_to_iso(x, y, z);
	if (camera->projection == TOP)
		return ;
	if (camera->projection == SIDE)
		conv_to_side(y, z);
	if (camera->projection == CAB)
		conv_to_cab(x, y, z);
	if (camera->projection == CAV)
		conv_to_cav(x, y, z);
}

void	recenter(t_map *dup, t_master *master, int row, int col)
{
	t_camera	*camera;

	camera = master->camera;
	dup->vmap[row][col].x += (int)master->img->width / 2 + camera->x_offset;
	dup->vmap[row][col].y += (int)master->img->height / 2 + camera->y_offset;
}
