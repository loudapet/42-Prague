/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:33:42 by plouda            #+#    #+#             */
/*   Updated: 2023/02/06 09:45:12 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

int	ft_printf_nbr(int nb)
{
	char	*str;
	int		len;

	str = ft_itoa(nb);
	len = ft_printf_str(str);
	free(str);
	return (len);
}
