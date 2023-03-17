/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:19:40 by plouda            #+#    #+#             */
/*   Updated: 2023/01/16 12:09:40 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	pos;

	i = 0;
	pos = -1;
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i] != 0)
	{
		if (s[i] == c % 256)
			pos = i;
		i++;
	}
	if (pos != -1)
		return ((char *)s + pos);
	return (0);
}
