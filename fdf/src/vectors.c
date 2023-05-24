/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:01:19 by plouda            #+#    #+#             */
/*   Updated: 2023/05/24 08:17:43 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	max_alt(t_tab tab)
{
	int		max;
	int		row;
	int		col;
	int		zcoor;

	max = tab.tab[0][0][0];
	row = 0;
	while (row < tab.nrows)
	{
		col = 0;
		while (col < tab.ncols)
		{
			zcoor = tab.tab[0][row][col];
			if (zcoor > max)
				max = zcoor;
			col++;
		}
		row++;
	}
	return (max);
}

int	min_alt(t_tab tab)
{
	int		min;
	int		row;
	int		col;
	int		zcoor;

	min = tab.tab[0][0][0];
	row = 0;
	while (row < tab.nrows)
	{
		col = 0;
		while (col < tab.ncols)
		{
			zcoor = tab.tab[0][row][col];
			if (zcoor < min)
				min = zcoor;
			col++;
		}
		row++;
	}
	return (min);
}

t_vector	**create_vectors(t_vector **vmap, int ***tab, int ncols, int row)
{
	int			col;
	t_vector	vector;

	col = 0;
	vmap[row] = malloc(ncols * sizeof(t_vector));
	if (!vmap[row])
		return (NULL);
	while (col < ncols)
	{
		vector.x = col;
		vector.y = row;
		vector.z = tab[0][row][col];
		vector.color = tab[1][row][col];
		vmap[row][col] = vector;
		col++;
	}
	return (vmap);
}

t_map	*tab_to_vect(t_tab *tab)
{
	t_map		*map;
	int			row;

	map = malloc(sizeof(t_map));
	map->vmap = malloc(sizeof(t_vector *) * tab->nrows);
	if (map->vmap == 0)
	{
		map->vmap = NULL;
		return (map);
	}
	map->z_max = max_alt(*tab);
	map->z_min = min_alt(*tab);
	row = 0;
	while (row < tab->nrows)
	{
		map->vmap = create_vectors(map->vmap, tab->tab, tab->ncols, row);
		row++;
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
