/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:43:40 by plouda            #+#    #+#             */
/*   Updated: 2023/01/16 17:19:41 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	len_src;
	unsigned int	len_dst;
	unsigned int	i;
	unsigned int	j;

	if (size == 0 && !dst)
		return (0);
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	i = 0;
	j = len_dst;
	if (size == 0 || size <= len_dst)
		return (len_src + size);
	while (src[i] != 0 && j + 1 < size)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = 0;
	return (len_dst + len_src);
}
