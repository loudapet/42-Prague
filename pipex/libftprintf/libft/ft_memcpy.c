/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:26:24 by plouda            #+#    #+#             */
/*   Updated: 2023/01/16 16:28:06 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ndest;
	unsigned char	*nsrc;
	unsigned int	i;

	if (dest == 0 && src == 0)
		return (dest);
	i = 0;
	ndest = (unsigned char *)dest;
	nsrc = (unsigned char *)src;
	while (i < n)
	{
		ndest[i] = nsrc[i];
		i++;
	}
	return (dest);
}
