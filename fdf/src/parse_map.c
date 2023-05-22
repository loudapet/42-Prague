/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:02:33 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 16:41:45 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_tab_content(int **map_array, int ncols, int nrows)
{
	int	j;

	j = 0;
	while (j < ncols)
	{
		ft_printf("%d ", map_array[nrows][j]);
		j++;
	}
	write(1, "\n", 1);
}

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
	if (map_fd < 0)
		return (-1);
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

static int	validate(int *valid, int new)
{
	if (valid[0] == -1)
	{
		valid[0] = new;
		valid[1] = new;
		return (0);
	}
	valid[0] = valid[1];
	valid[1] = new;
	if (valid[0] != valid[1])
		return (1);
	return (0);
}

t_tab	*parse_map(const char *path)
{
	t_tab	*map;
	int		map_fd;
	char	*row;
	char	**split_row;
	char	*trim_row;
	int		*validation;
	int		i;

	i = 0;
	map = malloc(sizeof(t_tab));
	map->nrows = row_count(path);
	map->ncols = 0;
	map_fd = open(path, O_RDONLY);
	if (map_fd < 0)
		map->nrows = -1;
	if (map->nrows <= 0)
		return (map);
	map->tab = malloc(2 * sizeof(int **));
	map->tab[0] = malloc(map->nrows * sizeof(int *));
	map->tab[1] = malloc(map->nrows * sizeof(int *));
	validation = malloc(2 * sizeof(int));
	if (!map->tab[0] || !map->tab[1] || !map->tab)
	{
		map->tab = NULL;
		free(validation);
		return (map);
	}
	validation[0] = -1;
	validation[1] = -1;
	row = get_next_line(map_fd);
	while (row)
	{
		trim_row = ft_strtrim(row, " \n");
		split_row = ft_split(trim_row, ' ');
		map->ncols = col_count(split_row);
		if (validate(validation, map->ncols))
		{
			free(trim_row);
			free_split(split_row);
			map->ncols = -1;
			map->nrows = i;
			break ;
		}
		map->tab = create_map_array(map->tab, split_row, map->ncols, i);
		free(row);
		free(trim_row);
		free_split(split_row);
		row = get_next_line(map_fd);
		i++;
	}
	free(validation);
	free(row);
	close(map_fd);
	return (map);
}
