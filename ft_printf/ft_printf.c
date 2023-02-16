/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:01:05 by plouda            #+#    #+#             */
/*   Updated: 2023/02/16 10:54:41 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_flags	ft_save_flags(char *fill)
{
	t_flags	flags;
	int		i;

	i = 0;
	flags.hashtag = 0;
	flags.space = 0;
	flags.plus = 0;
	while (ft_strchr("# +", fill[i]))
	{
		if (fill[i] == '#')
			flags.hashtag = 1;
		else if (fill[i] == ' ')
			flags.space = 1;
		else if (fill[i] == '+')
			flags.plus = 1;
		i++;
	}
	flags.specifier = fill[i];
	flags.count_fill = i;
	return (flags);
}

static int	ft_dispatch(va_list args, char c, t_flags flags)
{
	int	bytes;

	bytes = 0;
	if (c == 'c')
		bytes = ft_printf_char(va_arg(args, int));
	else if (c == 's')
		bytes = ft_printf_str(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		bytes = ft_printf_nbr(va_arg(args, int), flags);
	else if (c == 'u')
		bytes = ft_printf_unbr(va_arg(args, unsigned int));
	else if (c == 'x')
		bytes = ft_printf_hex(va_arg(args, unsigned int), 'x', flags);
	else if (c == 'X')
		bytes = ft_printf_hex(va_arg(args, unsigned int), 'X', flags);
	else if (c == 'p')
		bytes = ft_printf_ptr(va_arg(args, uintptr_t), flags);
	else if (c == '%')
		bytes = ft_printf_char(c);
	return (bytes);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		bytes;
	t_flags	flags;

	i = 0;
	bytes = 0;
	va_start(args, str);
	while (str[i] != 0)
	{
		if (str[i] == '%')
		{
			flags = ft_save_flags((char *)&str[i + 1]);
			bytes = bytes + ft_dispatch(args, flags.specifier, flags);
			i = i + flags.count_fill + 1;
		}
		else
			bytes = bytes + ft_printf_char(str[i]);
		i++;
	}
	va_end(args);
	return (bytes);
}
