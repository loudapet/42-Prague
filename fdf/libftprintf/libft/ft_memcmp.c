/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:54:10 by plouda            #+#    #+#             */
/*   Updated: 2023/01/16 15:29:16 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	char			*ns1;
	char			*ns2;

	ns1 = (char *)s1;
	ns2 = (char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (ns1[i] == ns2[i] && i < n - 1)
		i++;
	return ((unsigned char)ns1[i] - (unsigned char)ns2[i]);
}
