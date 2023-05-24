/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:21:22 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 14:22:01 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	rad_to_deg(double rad)
{
	double	deg;

	deg = rad * 180 / M_PI;
	return (deg);
}

double	deg_to_rad(double deg)
{
	double	rad;

	rad = deg * M_PI / 180;
	return (rad);
}

int	abs_val(int nb)
{
	if (nb < 0)
		nb = -nb;
	return (nb);
}
