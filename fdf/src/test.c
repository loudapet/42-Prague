/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:36:02 by plouda            #+#    #+#             */
/*   Updated: 2023/04/17 19:10:48 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:46:22 by plouda            #+#    #+#             */
/*   Updated: 2023/04/17 10:58:55 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include "MLX42/MLX42.h"
#include "fdf.h"
#define WIDTH 1920/2
#define HEIGHT 1080/2

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

/* void plot_pixel(int x1, int y1, int x2, int y2, int dx,
               int dy, int decide, mlx_image_t *line)
{
    // pk is initial decision making parameter
    // Note:x1&y1,x2&y2, dx&dy values are interchanged
    // and passed in plotPixel function so
    // it can handle both cases when m>1 & m<1
    int pk = 2 * dy - dx;
    for (int i = 0; i <= dx; i++) {
        // checking either to decrement or increment the
        // value if we have to plot from (0,100) to (100,0)
        x1 < x2 ? x1++ : x1--;
        if (pk < 0) {
            // decision value will decide to plot
            // either  x1 or y1 in x's position
            if (decide == 0) {
                // putpixel(x1, y1, RED);
				mlx_resize_image(line, line->instances[0].x += 1, line->instances[0].y += 1);
				mlx_put_pixel(line, x1, y1, 255);
                pk = pk + 2 * dy;
            }
            else {
                //(y1,x1) is passed in xt
                // putpixel(y1, x1, YELLOW);
				mlx_resize_image(line, line->instances[0].x += 1, line->instances[0].y += 1);
				mlx_put_pixel(line, x1, y1, 255);
                pk = pk + 2 * dy;
            }
        }
        else {
            y1 < y2 ? y1++ : y1--;
            if (decide == 0) {
                // putpixel(x1, y1, RED);
				mlx_resize_image(line, line->instances[0].x += 1, line->instances[0].y += 1);
				mlx_put_pixel(line, x1, y1, 255);
            }
            else {
                //  putpixel(y1, x1, YELLOW);
				mlx_resize_image(line, line->instances[0].x += 1, line->instances[0].y += 1);
				mlx_put_pixel(line, x1, y1, 255);
            }
            pk = pk + 2 * dy - 2 * dx;
        }
    }
}
void draw_line(mlx_key_data_t keydata, void* param)  
{
    mlx_image_t	*line;

	line = param;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		int x1 = 100, y1 = 110, x2 = 125, y2 = 120, dx, dy;
		dx = abs(x2 - x1);
		dy = abs(y2 - y1);
		// If slope is less than one
		if (dx > dy) 
		{
			// passing argument as 0 to plot(x,y)
			plot_pixel(x1, y1, x2, y2, dx, dy, 0, line);
		}
    	// if slope is greater than or equal to 1
    	else 
		{
			// passing argument as 1 to plot (y,x)
			plot_pixel(y1, x1, y2, x2, dy, dx, 1, line);
		}
	} */

void my_keyhook(mlx_key_data_t keydata, void* param)
{
	mlx_image_t	*img;

	img = param;
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
		img->instances[0].y += 20;
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
		img->instances[0].y -= 20;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		img->instances[0].x += 20;
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		img->instances[0].x -= 20;
	if (keydata.key == MLX_KEY_KP_ADD && keydata.action == MLX_PRESS)
		mlx_resize_image(img, img->instances[0].x += 25, img->instances[0].y += 25);
	if (keydata.key == MLX_KEY_KP_SUBTRACT && keydata.action == MLX_PRESS)
		mlx_resize_image(img, img->instances[0].x -= 25, img->instances[0].y -= 25);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	main(int argc, const char **argv)
{
	t_tab	map;
	
	if (argc == 2)
		map = parse_map(argv[1]);
	if (!map.tab)
		return (EXIT_FAILURE);
	// Start mlx
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
	if (!mlx)
        error();

	// Create a new image
	mlx_image_t* img = mlx_new_image(mlx, map.ncols, map.nrows);
	if (!img)
		error();

	// Set every other pixel to white
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	x = 0;		
	ft_printf("Width: %d\n", img->width);
	ft_printf("Height: %d\n", img->height);
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			if (map.tab[y][x] > 0)
			{
				color = get_rgba(
					254 % 0xFF, // R
					254 % 0xFF, // G
					254 % 0xFF, // B
					254 % 0xFF  // A
				);
			}
			else
			{
				color = get_rgba(
					130 % 0xFF, // R
					130 % 0xFF, // G
					130 % 0xFF, // B
					0 % 0xFF  // A
				);
			}
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
	
	
	// Display an instance of the image
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
        error();

    // Modify the x & y position of an already existing instance.
    //img->instances[0].x += 100;
    //img->instances[0].y += 100;
	//mlx_set_instance_depth(&img->instances[0], 1);

	mlx_key_hook(mlx, &my_keyhook, img);
	mlx_loop(mlx);

	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}