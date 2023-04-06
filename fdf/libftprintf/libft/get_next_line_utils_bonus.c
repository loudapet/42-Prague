/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <plouda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:40:38 by plouda            #+#    #+#             */
/*   Updated: 2023/03/30 09:20:53 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strllen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != 0)
		i++;
	return (i);
}

char	*ft_strchr_custom(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != 0)
	{
		if (*s == c % 256)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin_custom(char *s1, char *s2)
{
	char			*join;
	unsigned int	i;
	unsigned int	j;

	if (!s1)
	{
		s1 = (char *)malloc(1);
		s1[0] = 0;
	}
	join = (char *)malloc((ft_strllen(s1) + ft_strllen(s2)) * sizeof(char) + 1);
	if (!join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
		join[i++] = s2[j++];
	join[i] = 0;
	free(s1);
	return (join);
}
