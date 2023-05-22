/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:22:59 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 22:40:40 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	topo_bottom(double ratio)
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
	return (0x00000000);
}

static int	topo_top(double ratio)
{
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
	if (ratio <= 1)
		return (0xF5F4F2ff);
	return (0x00000000);
}

int	topo_palette(double ratio)
{
	if (ratio < 0.50)
		return (topo_bottom(ratio));
	else if (ratio <= 1)
		return (topo_top(ratio));
	return (0x00000000);
}

int	rainbow_palette(double ratio)
{
	if (ratio < 0.125)
		return (0xFFADADff);
	if (ratio < 0.25)
		return (0xFFD6A5ff);
	if (ratio < 0.375)
		return (0xFDFFB6ff);
	if (ratio < 0.50)
		return (0xCAFFBFff);
	if (ratio < 0.625)
		return (0x9BF6FFff);
	if (ratio < 0.75)
		return (0xA0C4FFff);
	if (ratio < 0.875)
		return (0xBDB2FFff);
	if (ratio <= 1)
		return (0xFFC6FFff);
	return (0x00000000);
}

int	sunrise_palette(double ratio)
{
	if (ratio < 0.125)
		return (0x003f5cff);
	if (ratio < 0.25)
		return (0x58508dff);
	if (ratio < 0.375)
		return (0x8a508fff);
	if (ratio < 0.50)
		return (0xbc5090ff);
	if (ratio < 0.625)
		return (0xde5a79ff);
	if (ratio < 0.75)
		return (0xff6361ff);
	if (ratio < 0.875)
		return (0xff8531ff);
	if (ratio <= 1)
		return (0xffa600ff);
	return (0x00000000);
}
