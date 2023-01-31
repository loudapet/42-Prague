/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:24:55 by plouda            #+#    #+#             */
/*   Updated: 2023/01/17 08:59:51 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ndest;	
	unsigned char	*nsrc;

	ndest = (unsigned char *)dest;
	nsrc = (unsigned char *)src;
	if (dest == 0 && src == 0)
		return (dest);
	if (ndest > nsrc && nsrc + n > ndest)
	{
		nsrc = nsrc + n;
		ndest = ndest + n;
		while (n-- > 0)
			*--ndest = *--nsrc;
	}
	else
	{
		while (n-- > 0)
			*ndest++ = *nsrc++;
	}
	return (dest);
}
