/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:05:55 by plouda            #+#    #+#             */
/*   Updated: 2023/01/16 15:31:10 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*ch1;
	unsigned char	*ch2;

	ch1 = (unsigned char *)s1;
	ch2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (ch1[i] != '\0' && ch1[i] == ch2[i] && i < n - 1)
		i++;
	return (ch1[i] - ch2[i]);
}
