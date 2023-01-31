/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:09:55 by plouda            #+#    #+#             */
/*   Updated: 2023/01/20 16:30:45 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	strlen;
	char			*copy;
	char			*substr;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start + len < strlen)
		copy = (char *)malloc(len * sizeof(char) + 1);
	else if (start >= strlen)
		copy = (char *)malloc(1);
	else
		copy = (char *)malloc((strlen - start) * sizeof(char) + 1);
	if (!copy)
		return (NULL);
	substr = copy;
	i = 0;
	if (start < strlen)
		while (s[start] != 0 && i < len)
			substr[i++] = s[start++];
	substr[i] = 0;
	return (copy);
}
