/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 17:27:06 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 17:29:25 by plouda           ###   ########.fr       */
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

int	validate(int *valid, int new)
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
