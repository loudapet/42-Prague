/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:09:51 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 14:15:03 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	alloc_rows(t_map *vmap, int nrows, int ncols)
{
	int	row;

	row = 0;
	while (row < nrows)
	{
		vmap->vmap[row] = malloc(sizeof(t_vector) * ncols);
		if (!vmap->vmap[row])
		{
			vmap = NULL;
			vmap->vmap = NULL;
			vmap->vmap[row] = NULL;
			return ;
		}
		row++;
	}
}

t_map	*allocate(int nrows, int ncols)
{
	t_map	*vmap;

	vmap = malloc(sizeof(t_map));
	if (!vmap)
	{
		vmap = NULL;
		return (vmap);
	}
	vmap->vmap = malloc(sizeof(t_vector *) * nrows);
	if (!vmap->vmap)
	{
		vmap = NULL;
		vmap->vmap = NULL;
		return (vmap);
	}
	alloc_rows(vmap, nrows, ncols);
	return (vmap);
}
