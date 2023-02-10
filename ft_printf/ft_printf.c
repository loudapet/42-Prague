/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:01:05 by plouda            #+#    #+#             */
/*   Updated: 2023/02/10 10:19:01 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"

static int	ft_dispatch(va_list args, char c)
{
	int	bytes;

	bytes = 0;
	if (c == 'c')
		bytes = ft_printf_char(va_arg(args, int));
	else if (c == 's')
		bytes = ft_printf_str(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		bytes = ft_printf_nbr(va_arg(args, int));
	else if (c == 'u')
		bytes = ft_printf_unbr(va_arg(args, unsigned int));
	else if (c == 'x')
		bytes = ft_printf_hex(va_arg(args, unsigned int), 'x');
	else if (c == 'X')
		bytes = ft_printf_hex(va_arg(args, unsigned int), 'X');
	else if (c == 'p')
		bytes = ft_printf_ptr(va_arg(args, uintptr_t));
	else if (c == '%')
		bytes = ft_printf_char(c);
	return (bytes);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		bytes;

	i = 0;
	bytes = 0;
	va_start(args, str);
	while (str[i] != 0)
	{
		if (str[i] == '%')
		{
			bytes = bytes + ft_dispatch(args, str[i+1]);
			i++;
		}
		else
			bytes = bytes + ft_printf_char(str[i]);
		i++;
	}
	va_end(args);
	return (bytes);
}
