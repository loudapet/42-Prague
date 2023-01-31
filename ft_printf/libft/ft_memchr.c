/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:58:40 by plouda            #+#    #+#             */
/*   Updated: 2023/01/16 14:53:28 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char			*ns;
	unsigned int	i;

	ns = (char *)s;
	i = 0;
	while (i < n)
	{
		if (*ns == c % 256)
			return ((char *)ns);
		i++;
		ns++;
	}
	return (0);
}
