/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:58:05 by plouda            #+#    #+#             */
/*   Updated: 2023/05/23 10:32:50 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_tab(t_tab *tab)
{
	int	row;

	row = 0;
	while (row < tab->nrows)
	{
		free(tab->tab[0][row]);
		free(tab->tab[1][row]);
		row++;
	}
	free(tab->tab[0]);
	free(tab->tab[1]);
	free(tab->tab);
	free(tab);
}

void	free_map(t_map *vmap)
{
	int	i;

	i = 0;
	while (i < vmap->nrows)
	{
		free(vmap->vmap[i]);
		i++;
	}
	free(vmap->vmap);
	free(vmap);
}

void	free_trimmed_split(char *trim, char **split, char *row, int flag)
{
	free(trim);
	free_split(split);
	if (flag)
		free(row);
}
