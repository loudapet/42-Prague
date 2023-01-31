/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:01:05 by plouda            #+#    #+#             */
/*   Updated: 2023/01/31 14:23:37 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int	ft_printf(const char *str, ...)
{
	if (!ft_strchr(str, '%'))
	{
		ft_putstr_fd((char *)str, 1);
		return (ft_strlen((char *)str));
	}
	return (0);
}