/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 11:37:22 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 14:13:46 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zoom(t_master *master, double ydelta)
{
	if (ydelta > 0)
	{
		master->camera->zoom += 1.;
		project(master);
	}
	if (ydelta < 0)
	{
		master->camera->zoom -= 1.;
		if (master->camera->zoom < 1.)
			master->camera->zoom = 1.;
		project(master);
	}
}

static void	translate(t_master *master, double xdelta)
{
	if (xdelta > 0)
	{
		master->camera->x_offset += 25;
		project(master);
	}
	if (xdelta < 0)
	{
		master->camera->x_offset -= 25;
		project(master);
	}
}

void	scrollhook(double xdelta, double ydelta, void *param)
{
	t_master	*master;

	master = param;
	zoom(master, ydelta);
	translate(master, xdelta);
}
