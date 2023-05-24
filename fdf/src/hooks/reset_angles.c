/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_angles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 11:04:28 by plouda            #+#    #+#             */
/*   Updated: 2023/05/23 11:08:30 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
Reset allows for infinite rotations. 179.5 degrees is less problematic
than 180, and the jump during reset is barely noticable.
*/
static void	a_reset(double *angle)
{
	if (*angle >= M_PI)
		*angle = deg_to_rad(-179.5);
	else if (*angle <= -M_PI)
		*angle = deg_to_rad(179.5);
}

void	reset_angles(t_camera *camera)
{
	if (camera->alpha >= M_PI || camera->alpha <= -M_PI)
		a_reset(&camera->alpha);
	if (camera->beta >= M_PI || camera->beta <= -M_PI)
		a_reset(&camera->beta);
	if (camera->gamma >= M_PI || camera->gamma <= -M_PI)
		a_reset(&camera->gamma);
}
