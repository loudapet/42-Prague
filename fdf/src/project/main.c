/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:07:29 by plouda            #+#    #+#             */
/*   Updated: 2023/05/24 13:47:07 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_validity(t_tab *map)
{
	if (!map->tab || map->ncols <= 0 || map->nrows <= 0)
	{
		if (map->nrows == -1)
		{
			free(map);
			write(2, "Invalid file\n", 14);
		}
		else if (map->nrows == 0)
		{
			free(map);
			write(2, "Empty file\n", 12);
		}
		else if (map->ncols == -1)
		{
			write(2, "Invalid map column range\n", 26);
			free_tab(map);
		}
		else
			write(2, "Allocation error\n", 18);
		return (1);
	}
	return (0);
}

static void	loop(mlx_t *mlx, t_master *master)
{
	mlx_key_hook(mlx, &keyhook, master);
	mlx_scroll_hook(mlx, &scrollhook, master);
	mlx_cursor_hook(mlx, &cursor, master);
	mlx_resize_hook(mlx, &resizehook, master);
	mlx_loop(mlx);
}

static void	terminate(t_master *master)
{
	mlx_delete_image(master->mlx, master->img);
	mlx_terminate(master->mlx);
	free_tab(master->map);
	free_map(master->vmap);
	free(master->camera);
	free(master->cursor);
	free(master);
}

mlx_t	*init_mlx(void)
{
	mlx_t		*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		error();
	mlx_set_window_limit(mlx, 250, 350, 10000, 10000);
	return (mlx);
}

int32_t	main(int argc, const char **argv)
{
	t_tab		*map;
	t_map		*vmap;
	mlx_image_t	*img;
	mlx_t		*mlx;
	t_master	*master;

	if (argc == 2)
	{
		map = parse_map(argv[1]);
		if (check_validity(map))
			return (EXIT_FAILURE);
		vmap = tab_to_vect(map);
		mlx = init_mlx();
		if (!mlx)
			return (EXIT_FAILURE);
		img = init_img(mlx);
		master = init_master(mlx, img, map, vmap);
		if (!master)
			return (EXIT_FAILURE);
		project(master);
		print_instructions(master);
		loop(mlx, master);
		terminate(master);
	}
	return (EXIT_SUCCESS);
}
