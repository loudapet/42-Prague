/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:37:56 by plouda            #+#    #+#             */
/*   Updated: 2023/02/16 09:52:11 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_unbr(unsigned int unb)
{
	char	*str;
	int		len;

	str = ft_uitoa(unb);
	len = ft_printf_str(str);
	free(str);
	return (len);
}
