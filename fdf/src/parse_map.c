/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:02:33 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 17:29:55 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	assign_clr(char **split, int ***map_array, int row, int col)
{
	if (split[1] != NULL)
	{
		map_array[0][row][col] = ft_atoi(split[0]);
		map_array[1][row][col] = (unsigned int)ft_atoi_base \
		(split[1] + 2, 16) * 256;
	}
	else
	{
		map_array[0][row][col] = ft_atoi(split[0]);
		map_array[1][row][col] = DEFAULT;
	}
}

int	***create_map_array(int ***map_array, char **split_row, int ncols, int row)
{
	int		col;
	char	**split;

	col = 0;
	map_array[0][row] = malloc(ncols * sizeof(int));
	map_array[1][row] = malloc(ncols * sizeof(int));
	if (!map_array[0][row] || !map_array[1][row])
		return (NULL);
	while (col < ncols)
	{
		split = ft_split(split_row[col], ',');
		assign_clr(split, map_array, row, col);
		free_split(split);
		col++;
	}
	return (map_array);
}

static void	create_map(t_tab *map)
{
	char	*row;
	char	**split_row;
	char	*trim_row;
	int		i;

	i = 0;
	row = get_next_line(map->map_fd);
	while (row)
	{
		trim_row = ft_strtrim(row, " \n");
		split_row = ft_split(trim_row, ' ');
		map->ncols = col_count(split_row);
		if (validate(map->validation, map->ncols))
		{
			free_trimmed_split(trim_row, split_row, row, 0);
			map->ncols = -1;
			map->nrows = i;
			break ;
		}
		map->tab = create_map_array(map->tab, split_row, map->ncols, i);
		free_trimmed_split(trim_row, split_row, row, 1);
		row = get_next_line(map->map_fd);
		i++;
	}
	free(row);
}

t_tab	*parse_map(const char *path)
{
	t_tab	*map;

	map = init_tab(path);
	if (!map || !map->tab)
		return (map);
	create_map(map);
	close(map->map_fd);
	return (map);
}
