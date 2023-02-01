/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:37:56 by plouda            #+#    #+#             */
/*   Updated: 2023/02/01 11:39:46 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"

static int	ft_places(unsigned int n)
{
	unsigned char	places;

	places = 0;
	while (n > 9)
	{
		n = n / 10;
		places++;
	}
	if (n <= 9)
		places++;
	return (places);
}

static char	*ft_convert(char *str, int i, unsigned int n)
{
	int	mod;

	while (i >= 0)
	{
		mod = n % 10;
		str[i--] = (char)(mod + '0');
		n = n / 10;
	}
	return (str);
}

static char	*ft_uitoa(unsigned int n)
{
	
	unsigned int	i;
	char			*str;

	i = ft_places(n) + 1;
	str = malloc(i * sizeof(char));
	if (!str)
		return (NULL);
	i--;
	str[i] = 0;
	i--;
	return (ft_convert(str, i, n));
}

int	ft_printf_unbr(unsigned int unb)
{
	char	*str;
	int		len;

	str = ft_uitoa(unb);
	len = ft_printf_str(str);
	free(str);
	return (len);
}