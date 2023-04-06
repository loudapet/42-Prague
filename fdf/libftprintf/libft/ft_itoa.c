/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:06:43 by plouda            #+#    #+#             */
/*   Updated: 2023/01/19 12:36:24 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isneg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static int	ft_places(int n)
{
	unsigned char	places;

	places = 0;
	if (ft_isneg(n))
		places++;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		places++;
	}
	if ((n >= 0 && n <= 9) || (n >= -9 && n <= 0))
		places++;
	return (places);
}

static char	*ft_min_int(char *str)
{
	ft_strlcpy(str, "-2147483648", 12);
	return (str);
}

static char	*ft_convert(char *str, int i, int n, int flag)
{
	int	mod;

	while (i >= 0)
	{
		if (i == 0 && flag == 1)
		{
			str[0] = '-';
			break ;
		}
		mod = n % 10;
		str[i--] = (char)(mod + '0');
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*str;
	int				flag;

	flag = ft_isneg(n);
	i = ft_places(n) + 1;
	str = malloc(i * sizeof(char));
	if (!str)
		return (NULL);
	i--;
	str[i] = 0;
	i--;
	if (flag == 1 && n != -2147483648)
		n = n * -1;
	else if (n == -2147483648)
		return (ft_min_int(str));
	return (ft_convert(str, i, n, flag));
}
