/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:08:36 by plouda            #+#    #+#             */
/*   Updated: 2023/02/07 16:54:57 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

static int	ft_strrev(char *str)
{
	char	*rev;
	int		i;
	int		j;
	int		bytes;

	i = 0;
	j = ft_strlen(str) + 1;
	rev = malloc(j * sizeof(char));
	if (!rev)
		return (0);
	j--;
	rev[j] = 0;
	j--;
	while (j >= 0)
	{
		rev[j] = str[i];
		j--;
		i++;
	}
	free(str);
	bytes = ft_printf_str(rev);
	free(rev);
	return (bytes);
}

static char	ft_convert(uintptr_t mod)
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

// Why ft_places + 3 and not + 1? (valgrind)
static int	ft_printf_hexptr(uintptr_t unb, char flag)
{
	char			*str;
	unsigned int	mod;
	int				i;
	int				bytes;

	if (unb == 0)
		return (ft_printf_nbr(0));
	str = ft_calloc(ft_places(unb) + 3, sizeof(char));
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
	bytes = ft_strrev(str);
	return (bytes);
}

int	ft_printf_ptr(uintptr_t n)
{
	if (n == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	return(ft_printf_hexptr((uintptr_t)n, 'x') + 2);
}