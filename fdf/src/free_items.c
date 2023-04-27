/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:58:05 by plouda            #+#    #+#             */
/*   Updated: 2023/04/27 17:58:30 by plouda           ###   ########.fr       */
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

void	free_tab(t_tab tab)
{
	int	row;

	row = 0;
	while (row < tab.nrows)
	{
		free(tab.tab[row]);
		row++;
	}
	free(tab.tab);
}

void	free_map(t_map map)
{
	int	i;

	i = 0;
	while (i < map.nrows)
	{
		free(map.vmap[i]);
		i++;
	}
	free(map.vmap);
}
