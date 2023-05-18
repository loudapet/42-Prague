/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:22:59 by plouda            #+#    #+#             */
/*   Updated: 2023/05/18 18:02:36 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	topo_palette(double ratio)
{
	if (ratio == 0)
		return (0x8DC1EAff);
	if (ratio < 0.10)
		return (0xACD0A5ff);
	if (ratio < 0.15)
		return (0x94BF8Bff);
	if (ratio < 0.20)
		return (0xA8C68Fff);
	if (ratio < 0.25)
		return (0xBDCC96ff);
	if (ratio < 0.30)
		return (0xD1D7ABff);
	if (ratio < 0.35)
		return (0xE1E4B5ff);
	if (ratio < 0.40)
		return (0xEFEBC0ff);
	if (ratio < 0.45)
		return (0xE8E1B6ff);
	if (ratio < 0.50)
		return (0xDED6A3ff);
	if (ratio < 0.55)
		return (0xD3CA9Dff);
	if (ratio < 0.60)
		return (0xCAB982ff);
	if (ratio < 0.65)
		return (0xB9985Aff);
	if (ratio < 0.70)
		return (0xAA8753ff);
	if (ratio < 0.75)
		return (0xAC9A7Cff);
	if (ratio < 0.80)
		return (0xBAAE9Aff);
	if (ratio < 0.85)
		return (0xCAC3B8ff);
	if (ratio < 0.90)
		return (0xE0DED8ff);
	if (ratio < 0.95)
		return (0xF5F4F2ff);
	if (ratio == 1)
		return (0xF5F4F2ff);
	return (0x00000000);
}

int	rainbow_palette(double ratio)
{
	if (ratio < 0.17)
		return (0x9C4F96ff);
	if (ratio < 0.34)
		return (0xFF6355ff);
	if (ratio < 0.49)
		return (0xFBA949ff);
	if (ratio < 0.66)
		return (0xFAE442ff);
	if (ratio < 0.83)
		return (0x8BD448ff);
	if (ratio <= 1)
		return (0x2AA8F2ff);
	return (0x00000000);
}
