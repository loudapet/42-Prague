/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:07:29 by plouda            #+#    #+#             */
/*   Updated: 2023/05/03 09:09:39 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42/MLX42.h"
#define WIDTH 1600
#define HEIGHT 900

void calc_direction(t_line *line)
{
	if (line->x2 > line->x1)
		line->flag_x = 1;
	else
		line->flag_x = -1;
	if (line->y2 > line->y1)
		line->flag_y = 1;
	else
		line->flag_y = -1;
}

void calc_err(t_line *line, int *cur_p, int delta, int flag)
{
	int decision;

	if (line->dx > line->dy)
		decision = line->dx;
	else
		decision = line->dy;
	if (line->err > 0)
	{
		*cur_p += flag;
		line->err -= 2 * decision;
	}
	line->err += 2 * delta;
}

t_line init_vars(t_vector p1, t_vector p2)
{
	t_line line;

	line.x1 = (int)p1.x;
	line.x2 = (int)p2.x;
	line.y1 = (int)p1.y;
	line.y2 = (int)p2.y;

	if (abs_val(line.y2 - line.y1) < abs_val(line.x2 - line.x1))
	{
		if (line.x1 > line.x2)
			ft_swap(&line);
	}
	else
	{
		if (line.y1 > line.y2)
			ft_swap(&line);
	}
	line.dx = abs_val(line.x2 - line.x1);
	line.dy = abs_val(line.y2 - line.y1);
	calc_direction(&line);
	line.cur_x = line.x1;
	line.cur_y = line.y1;
	return (line);
}

void draw_line(mlx_image_t *img, t_vector p1, t_vector p2)
{
	t_line line;
	int color;

	color = get_rgba(
		254 % 0xFF, // R
		254 % 0xFF, // G
		254 % 0xFF, // B
		254 % 0xFF	// A
	);
	line = init_vars(p1, p2);
	if (line.dx > line.dy)
	{
		line.err = 2 * line.dy - line.dx;
		while (line.cur_x < line.x2)
		{
			if ((line.cur_x >= 0 && line.cur_y >= 0) && (line.cur_x < (int)img->width && line.cur_y < (int)img->height))
				mlx_put_pixel(img, line.cur_x, line.cur_y, color);
			line.cur_x += line.flag_x;
			calc_err(&line, &line.cur_y, line.dy, line.flag_y);
		}
	}
	else
	{
		line.err = 2 * line.dx - line.dy;
		while (line.cur_y < line.y2)
		{
			if ((line.cur_x >= 0 && line.cur_y >= 0) && (line.cur_x < (int)img->width && line.cur_y < (int)img->height))
				mlx_put_pixel(img, line.cur_x, line.cur_y, color);
			line.cur_y += line.flag_y;
			calc_err(&line, &line.cur_x, line.dx, line.flag_x);
		}
	}
}

void create_raster(mlx_image_t *img, t_map map)
{
	int y;
	int x;

	y = 0;
	while (y <= map.nrows - 1)
	{
		x = 0;
		while (x <= map.ncols - 1)
		{
			if (x == map.ncols - 1 && y == map.nrows - 1)
				break;
			if (x == map.ncols - 1 || y == map.nrows - 1)
			{
				if (x == map.ncols - 1)
					draw_line(img, map.vmap[y][x], map.vmap[y + 1][x]);
				if (y == map.nrows - 1)
					draw_line(img, map.vmap[y][x], map.vmap[y][x + 1]);
			}
			else
			{
				draw_line(img, map.vmap[y][x], map.vmap[y][x + 1]);
				draw_line(img, map.vmap[y][x], map.vmap[y + 1][x]);
			}
			x++;
		}
		y++;
	}
}

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

mlx_image_t *init_img(mlx_t *mlx)
{
	mlx_image_t *img;

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		error();
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		error();
	return (img);
}

void	my_scrollhook(double xdelta, double ydelta, void* param)
{
	t_master	*master;
	t_map	*vmap;

	master = param;
	vmap = master->vmap;
	if (ydelta > 0)
	{
		reset_img(master->img);
		zoom(vmap, 0.1);
		create_raster(master->img, *vmap);
	}
	if (ydelta < 0)
	{
		reset_img(master->img);
		zoom(vmap, -0.1);
		create_raster(master->img, *vmap);
	}
	if (xdelta > 0)
	{
		reset_img(master->img);
		horizontal_shift(vmap, 50);
		create_raster(master->img, *vmap);
	}
	if (xdelta < 0)
	{
		reset_img(master->img);
		horizontal_shift(vmap, -50);
		create_raster(master->img, *vmap);
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_tab	map;
	t_master	*master;
	t_map	*vmap;
	mlx_image_t	*img;

	master = param;
	vmap = master->vmap;
	img = master->img;
	map = master->map;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		horizontal_shift(vmap, 50);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		horizontal_shift(vmap, -50);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		vertical_shift(vmap, -50);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		vertical_shift(vmap, 50);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		rotate_z(vmap, -1);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		rotate_z(vmap, 1);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		rotate_y(vmap, 1);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		rotate_y(vmap, -1);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		rotate_x(vmap, 1);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		reset_img(master->img);
		rotate_x(vmap, -1);
		create_raster(master->img, *vmap);
	}
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		free_map(vmap);
		vmap = tab_to_vect(&map);
		reset_img(img);
		recenter_vertices(vmap, img);
		rotate_vertices(vmap);
		recenter_vertices(vmap, img);
		scale_vertices(vmap, img);
		recenter_vertices(vmap, img);
		create_raster(img, *vmap);
		master->img = img;
		master->vmap = vmap;
		master->map = map;
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		free_tab(map);
		free_map(vmap);
		mlx_delete_image(master->mlx, img);
		mlx_close_window(master->mlx);
	}
}

void	drag_image(double xpos, double ypos, t_master *master)
{
	t_mid	mid;
	t_map	*vmap;
	int		row;
	int		col;

	//printf("X: %f, Y: %f\n", xpos, ypos);
	vmap = master->vmap;
	mid = get_midpoint(*vmap);
	row = 0;
	while (row < vmap->nrows)
	{
		col = 0;
		while (col < vmap->ncols)
		{
			vmap->vmap[row][col].x += -mid.mid_x + (float)xpos;
			vmap->vmap[row][col].y += -mid.mid_y + (float)ypos;
			col++;
		}
		//print_vectors(vmap->vmap, vmap->ncols, row);
		row++;
	}
}

void	my_cursor(double xpos, double ypos, void* param)
{
	t_master	*master;
	t_map	*vmap;

	master = param;
	vmap = master->vmap;
	if (mlx_is_mouse_down(master->mlx, MLX_MOUSE_BUTTON_LEFT) &&
		xpos > 0 && ypos > 0)
	{
		reset_img(master->img);
		drag_image(xpos, ypos, master);
		create_raster(master->img, *vmap);
	}
}

void my_mousehook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_master	*master;
	t_map	*vmap;
	int32_t	xpos;
	int32_t	ypos;

	master = param;
	vmap = master->vmap;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		mlx_get_mouse_pos(master->mlx, &xpos, &ypos);
		reset_img(master->img);
		drag_image(xpos, ypos, master);
		create_raster(master->img, *vmap);
	}
	if (!mods)
		return ;
}

int32_t main(int argc, const char **argv)
{
	t_tab map;
	t_map *vmap;
	mlx_image_t *img;
	mlx_t *mlx;
	t_master	*master;

	if (argc == 2)
		map = parse_map(argv[1]);
	if (!map.tab)
		return (EXIT_FAILURE);
	vmap = tab_to_vect(&map);
	vmap->path = argv[1];
	mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
		error();
	img = init_img(mlx);
	vmap->img = img;

	reset_img(img);

	recenter_vertices(vmap, img);
	rotate_vertices(vmap);
	recenter_vertices(vmap, img);
	scale_vertices(vmap, img);
	recenter_vertices(vmap, img);
	create_raster(img, *vmap);

	master = malloc(sizeof(t_master));
	if (!master)
		return (EXIT_FAILURE);
	master->mlx = mlx;
	master->img = img;
	master->vmap = vmap;
	master->map = map;
	mlx_key_hook(mlx, &my_keyhook, master);
	mlx_scroll_hook(mlx, &my_scrollhook, master);
	mlx_mouse_hook(mlx, &my_mousehook, master);
	mlx_cursor_hook(mlx, &my_cursor, master);
	mlx_loop(mlx);

	mlx_terminate(master->mlx);
	free(master);
	return (EXIT_SUCCESS);
}