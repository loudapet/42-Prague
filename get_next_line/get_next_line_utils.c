/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:40:38 by plouda            #+#    #+#             */
/*   Updated: 2023/01/25 16:20:14 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != 0)
		i++;
	return (i);
}

/* why is the first condition needed? it should default to NULL if s doesn't 
exist (but it segfaults when the condition isn't there) */
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

/* initial function call will always be empty, so we need to allocate 
1 byte to s1 for strjoin to work where we need it (while reading file)*/
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
	join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
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
