/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:30:04 by plouda            #+#    #+#             */
/*   Updated: 2023/05/24 09:54:29 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	conv_to_iso(double *x, double *y, double *z)
{
	double	prev_x;
	double	prev_y;
	double	angle;

	angle = deg_to_rad(30);
	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(angle);
	*y = (prev_x + prev_y) * sin(angle) - (*z);
}

void	conv_to_side(double *y, double *z)
{
	double	angle;

	angle = deg_to_rad(-90);
	rot_x(y, z, angle);
}

void	conv_to_cab(double *x, double *y, double *z)
{
	double	angle;

	angle = deg_to_rad(-90);
	rot_x(y, z, angle);
	angle = deg_to_rad(45);
	*x = (*x) + (*z) * cos(angle) * 0.5;
	*y = (*y) + (*z) * sin(angle) * 0.5;
}

void	conv_to_cav(double *x, double *y, double *z)
{
	double	angle;

	angle = deg_to_rad(-90);
	rot_x(y, z, angle);
	angle = deg_to_rad(45);
	*x = (*x) + (*z) * cos(angle);
	*y = (*y) + (*z) * sin(angle);
}
