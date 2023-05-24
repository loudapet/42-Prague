/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_instructions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 22:22:59 by plouda            #+#    #+#             */
/*   Updated: 2023/05/22 22:23:09 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_instructions(t_master *master)
{
	int32_t	x;

	x = 15;
	master->instr = mlx_put_string(master->mlx, "Reset:            R", x, 5);
	master->instr = mlx_put_string(master->mlx, "Move:    Arrow Keys", x, 25);
	master->instr = mlx_put_string(master->mlx, "Zoom:        Scroll", x, 45);
	master->instr = mlx_put_string(master->mlx, "Rotate z:       Q/E", x, 65);
	master->instr = mlx_put_string(master->mlx, "Rotate y:       A/D", x, 85);
	master->instr = mlx_put_string(master->mlx, "Rotate x:       W/S", x, 105);
	master->instr = mlx_put_string(master->mlx, "Flatten/raise:  Z/X", x, 125);
	master->instr = mlx_put_string(master->mlx, "Recenter:         T", x, 145);
	master->instr = mlx_put_string(master->mlx, "Change color:     C", x, 165);
	master->instr = mlx_put_string(master->mlx, "Swap projection:  P", x, 185);
	master->instr = mlx_put_string(master->mlx, "ISOMETRIC          ", x, 215);
	master->instr = mlx_put_string(master->mlx, "TOP VIEW           ", x, 235);
	master->instr = mlx_put_string(master->mlx, "SIDE VIEW          ", x, 255);
	master->instr = mlx_put_string(master->mlx, "CABINET            ", x, 275);
	master->instr = mlx_put_string(master->mlx, "CAVALIER           ", x, 295);
}
