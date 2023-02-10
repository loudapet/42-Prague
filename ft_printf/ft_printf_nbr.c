/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:33:42 by plouda            #+#    #+#             */
/*   Updated: 2023/02/10 14:42:04 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int	ft_printf_nbr(int nb, t_flags flags)
{
	char	*str;
	int		len;

	if (nb >= 0)
		len = ft_flag_handler(flags, '+');
	else
		len = ft_flag_handler(flags, '-');
	str = ft_itoa(nb);
	len = len + ft_printf_str(str);
	free(str);
	return (len);
}
