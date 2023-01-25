/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:57:45 by plouda            #+#    #+#             */
/*   Updated: 2023/01/16 12:03:24 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;

	i = 0;
	if (little[0] == 0)
		return ((char *)big);
	if (len == 0)
		return (0);
	if (len == 1 && little[1] == 0)
		return (ft_strchr(big, little[0]));
	while (big[i] != 0 && i <= len - ft_strlen(little))
	{
		if (big[i] == little[0])
		{
			if (ft_strncmp(&big[i], &little[0], ft_strlen(little)) == 0)
				return ((char *)big + i);
		}
		i++;
	}
	return (0);
}
