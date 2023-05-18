/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:02:33 by plouda            #+#    #+#             */
/*   Updated: 2023/05/18 15:58:16 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_tab_content(int **map_array, int ncols, int nrows)
{
	int	j;
	
	j = 0;
	while (j < ncols)
	{
		ft_printf("%x ", map_array[nrows][j]);
		j++;
	}
	write(1, "\n", 1);
}

int	***create_map_array(int ***map_array, char **split_row, int count, int nrow)
{
	int	i;
	char	**split;

	i = 0;
	map_array[0][nrow] = malloc(count * sizeof(int));
	map_array[1][nrow] = malloc(count * sizeof(int));
	if (!map_array[0][nrow] || !map_array[1][nrow])
		return (NULL);
	while (i < count)
	{
		split = ft_split(split_row[i], ',');
		if (split[1] != NULL)
		{
			map_array[0][nrow][i] = ft_atoi(split[0]);
			map_array[1][nrow][i] = (unsigned int)ft_atoi_base(split[1] + 2, 16) * 256;
		}
		else
		{
			map_array[0][nrow][i] = ft_atoi(split[0]);
			map_array[1][nrow][i] = -1;
		}
		free_split(split);
		//ft_printf("Element saved: %d\n", map_array[0][nrow][i]);
		i++;
	}
	return (map_array);
}

int	col_count(char **array)
{
	int	i;

	i = 0;
	while (*array)
	{
		i++;
		array++;
	}
	return (i);
}

int	row_count(const char *path)
{
	int		map_fd;
	char	*row;
	int		i;

	i = 0;
	map_fd = open(path, O_RDONLY);
	row = get_next_line(map_fd);
	while (row)
	{
		free(row);
		row = get_next_line(map_fd);
		i++;
	}
	free(row);
	close(map_fd);
	return (i);	
}

t_tab *parse_map(const char *path)
{
	t_tab	*map;
	int		map_fd;
	char	*row;
	char	**split_row;
	int		i;

	i = 0;
	map = malloc(sizeof(t_tab));
	map->nrows = row_count(path);
	map_fd = open(path, O_RDONLY);
	map->tab = malloc(2 * sizeof(int **));
	map->tab[0] = malloc(map->nrows * sizeof(int *));
	map->tab[1] = malloc(map->nrows * sizeof(int *));
	if (!map->tab[0] || !map->tab[1] || !map->tab)
	{
		map->tab = NULL;
		return (map);
	}
	row = get_next_line(map_fd);
	while (row)
	{
		split_row = ft_split(row, ' ');
		map->ncols = col_count(split_row);
		map->tab = create_map_array(map->tab, split_row, map->ncols, i);
		print_tab_content(map->tab[1], map->ncols, i);
		free(row);
		free_split(split_row);
		row = get_next_line(map_fd);
		i++;
	}
	free(row);
	close(map_fd);
	return (map);
}