/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:31:09 by plouda            #+#    #+#             */
/*   Updated: 2023/01/20 16:30:24 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	total_len;
	char			*dest;
	char			*join;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(total_len * sizeof(char) + 1);
	if (!join)
		return (NULL);
	dest = join;
	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
		dest[i++] = s2[j++];
	dest[i] = 0;
	return (join);
}
