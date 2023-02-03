/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:55:15 by plouda            #+#    #+#             */
/*   Updated: 2023/02/03 14:48:57 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"
#include <stdio.h>


static char	*ft_strrev(char *str)
{
	char	*rev;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(str) + 1;
	rev = malloc(j *  sizeof(char));
	if (!rev)
		return (NULL);
	j--;
	rev[j] = 0;
	j--;
	while (j >= 0)
	{
		rev[j] = str[i];
		j--;
		i++;
	}
	return (rev);
}

static char	ft_convert(unsigned int mod)
{
	if (mod == 10)
		return ('a');
	else if (mod == 11)
		return ('b');
	else if (mod == 12)
		return ('c');
	else if (mod == 13)
		return ('d');
	else if (mod == 14)
		return ('e');
	else if (mod == 15)
		return ('f');
	return (mod);
}

static int	ft_places(unsigned int unb)
{
	int	i;

	i = 0;
	while (unb > 0)
	{
		unb = unb / 16;
		i++;
	}
	return (i);
}

int	ft_printf_hex(unsigned int unb, char flag)
{
	char	*str;
	unsigned int		mod;
	int		i;
	int		bytes;

	str = malloc((ft_places(unb) + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (unb > 0)
	{
		mod = unb % 16;
		if (mod > 9 && flag == 'X')
			str[i] = ft_convert(mod) - 32;
		else if (mod > 9 && flag == 'x')
			str[i] = ft_convert(mod);
		else
			str[i] = (char)(mod + 48);
		unb = unb / 16;
		i++;
	}
	bytes =	ft_printf_str(ft_strrev(str));
	return (bytes);
}