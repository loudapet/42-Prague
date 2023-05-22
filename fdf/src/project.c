/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:18:39 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 22:26:31 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	copy_vect(t_map *vmap, t_map *dup, int row, int col)
{
	dup->vmap[row][col].x = vmap->vmap[row][col].x;
	dup->vmap[row][col].y = vmap->vmap[row][col].y;
	dup->vmap[row][col].z = vmap->vmap[row][col].z;
}

static void	assign_clr(t_map *dup, int **tab, int row, int col)
{
	if (tab[row][col] > -4 && tab[row][col] < 0)
	{
		dup->vmap[row][col].color = \
		get_default_clr(dup->vmap[row][col].z, \
						dup->z_min, \
						dup->z_max, \
						dup->clr_flag);
	}
	else
		dup->vmap[row][col].color = tab[row][col];
}

static t_map	*vectdup(t_map *vmap, int **tab)
{
	t_map	*dup;
	int		row;
	int		col;

	dup = allocate(vmap->nrows, vmap->ncols);
	dup->nrows = vmap->nrows;
	dup->ncols = vmap->ncols;
	dup->z_max = vmap->z_max;
	dup->z_min = vmap->z_min;
	dup->clr_flag = vmap->clr_flag;
	row = 0;
	while (row < vmap->nrows)
	{
		col = 0;
		while (col < vmap->ncols)
		{
			copy_vect(vmap, dup, row, col);
			assign_clr(dup, tab, row, col);
			col++;
		}
		row++;
	}
	return (dup);
}

void	project(t_master *master)
{
	int			row;
	int			col;
	t_map		*dup;
	t_camera	*camera;

	reset_img(master->img);
	dup = vectdup(master->vmap, master->map->tab[1]);
	camera = master->camera;
	row = 0;
	while (row < dup->nrows)
	{
		col = 0;
		while (col < dup->ncols)
		{
			scale_and_zoom(dup, camera, row, col);
			shift_to_origin(dup, camera, row, col);
			rotate_xyz(dup, camera, row, col);
			convert_projection(dup, camera, row, col);
			recenter(dup, master, row, col);
			col++;
		}
		row++;
	}
	create_raster(master->img, *dup);
	free_map(dup);
}
