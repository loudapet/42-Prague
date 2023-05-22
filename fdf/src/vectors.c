/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:01:19 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 14:30:44 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	max_alt(t_tab tab)
{
	float	max;
	int		y;
	int		x;
	float	zcoor;

	max = tab.tab[0][0][0];
	y = 0;
	while (y < tab.nrows)
	{
		x = 0;
		while (x < tab.ncols)
		{
			zcoor = tab.tab[0][y][x];
			if (zcoor > max)
				max = zcoor;
			x++;
		}
		y++;
	}
	return (max);
}

float	min_alt(t_tab tab)
{
	float	min;
	int		y;
	int		x;
	float	zcoor;

	min = tab.tab[0][0][0];
	y = 0;
	while (y < tab.nrows)
	{
		x = 0;
		while (x < tab.ncols)
		{
			zcoor = tab.tab[0][y][x];
			if (zcoor < min)
				min = zcoor;
			x++;
		}
		y++;
	}
	return (min);
}

t_vector	**create_vectors(t_vector **vmap, int ***tab, int ncols, int nrow)
{
	int			i;
	t_vector	vector;

	i = 0;
	vmap[nrow] = malloc(ncols * sizeof(t_vector));
	if (!vmap[nrow])
		return (NULL);
	while (i < ncols)
	{
		vector.x = i;
		vector.y = nrow;
		vector.z = tab[0][nrow][i];
		vector.color = tab[1][nrow][i];
		vmap[nrow][i] = vector;
		i++;
	}
	return (vmap);
}

t_map	*tab_to_vect(t_tab *tab)
{
	t_map		*map;
	int			y;

	map = malloc(sizeof(t_map));
	map->vmap = malloc(sizeof(t_vector *) * tab->nrows);
	if (map->vmap == 0)
	{
		map->vmap = NULL;
		return (map);
	}
	map->z_max = max_alt(*tab);
	map->z_min = min_alt(*tab);
	y = 0;
	while (y < tab->nrows)
	{
		map->vmap = create_vectors(map->vmap, tab->tab, tab->ncols, y);
		y++;
	}
	map->ncols = tab->ncols;
	map->nrows = tab->nrows;
	map->clr_flag = DEFAULT;
	return (map);
}

/* void	print_vectors(t_vector **vmap, int ncols, int nrows)
{
	int	j;

	j = 0;
	ft_printf(" x, ");
	ft_printf("y, ");
	ft_printf("z \n");
	while (j < ncols)
	{
		printf("(%f, ", vmap[nrows][j].x);
		printf("%f, ", vmap[nrows][j].y);
		printf("%f) \n", vmap[nrows][j].z);
		j++;
	}
	write(1, "\n", 1);
} */
