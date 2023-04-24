/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:02:33 by plouda            #+#    #+#             */
/*   Updated: 2023/04/24 18:49:54 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_tab_content(int **map_array, int ncols, int nrows)
{
	int	j;
	
	while (j < ncols)
	{
		ft_printf("%d ", map_array[nrows][j]);
		j++;
	}
	write(1, "\n", 1);
}

int	**create_map_array(int **map_array, char **split_row, int count, int nrow)
{
	int	i;

	i = 0;
	map_array[nrow] = malloc(count * sizeof(int));
	if (!map_array[nrow])
		return (NULL);
	while (i < count)
	{
		map_array[nrow][i] = ft_atoi(split_row[i]);
		//ft_printf("Element saved: %d\n", map_array[nrow][i]);
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
		row = get_next_line(map_fd);
		i++;
	}
	free(row);
	close(map_fd);
	return (i);	
}

t_tab parse_map(const char *path)
{
	t_tab	map;
	int		map_fd;
	char	*row;
	char	**split_row;
	int		i;

	i = 0;
	map.nrows = row_count(path);
	map_fd = open(path, O_RDONLY);
	map.tab = malloc(map.nrows * sizeof(int **));
	if (!map.tab)
	{
		map.tab = NULL;
		return (map);
	}
	row = get_next_line(map_fd);
	while (row)
	{
		split_row = ft_split(row, ' ');
		map.ncols = col_count(split_row);
		map.tab = create_map_array(map.tab, split_row, map.ncols, i);
		//print_tab_content(map.tab, map.ncols, i);
		row = get_next_line(map_fd);
		free(split_row);
		i++;
	}
	free(row);
	close(map_fd);
	return (map);
}