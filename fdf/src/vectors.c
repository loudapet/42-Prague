/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:01:19 by plouda            #+#    #+#             */
/*   Updated: 2023/05/03 09:03:35 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_vectors(t_vector **vmap, int ncols, int nrows)
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
}

t_vector	**create_vectors(t_vector **vmap, int **tab, int ncols, int nrow)
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
		vector.z = tab[nrow][i];
		//vector.t = 1;
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
	y = 0;
	while (y < tab->nrows)
	{
		map->vmap = create_vectors(map->vmap, tab->tab, tab->ncols, y);
		//print_vectors(map->vmap, tab.ncols, y);
		y++;
	}
	map->ncols = tab->ncols;
	map->nrows = tab->nrows;
	//free_tab(tab);
	return (map);
}
