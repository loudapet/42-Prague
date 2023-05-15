/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:30:04 by plouda            #+#    #+#             */
/*   Updated: 2023/05/15 13:31:00 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	conv_to_iso(float *x, float *y, float *z)
{
	float	prev_x;
	float	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(0.5236);
	*y = (prev_x + prev_y) * sin(0.5236) - (*z);
}

void	conv_to_side(float *y, float *z)
{
	float	prev_y;
	float	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(1.57) - prev_z * sin(1.57);
	*z = prev_y * sin(1.57) + prev_z * cos(1.57);
}

void	conv_to_cab(float *x, float *y, float *z)
{
	float	prev_x;
	float	prev_y;
	float	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(1.57) - prev_z * sin(1.57);
	*z = prev_y * sin(1.57) + prev_z * cos(1.57);
	prev_x = *x;
	prev_y = *y;
	*x = prev_x + (*z) * cos(1) * 0.5;
	*y = prev_y + (*z) * sin(1) * 0.5;
}

void	conv_to_cav(float *x, float *y, float *z)
{
	float	prev_x;
	float	prev_y;
	float	prev_z;

	prev_y = *y;
	prev_z = *z;
	*y = prev_y * cos(1.57) - prev_z * sin(1.57);
	*z = prev_y * sin(1.57) + prev_z * cos(1.57);
	prev_x = *x;
	prev_y = *y;
	*x = prev_x + (*z) * cos(1);
	*y = prev_y + (*z) * sin(1);
}
