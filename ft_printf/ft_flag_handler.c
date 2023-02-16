/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:06:07 by plouda            #+#    #+#             */
/*   Updated: 2023/02/16 09:52:47 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_space(void)
{
	write(1, " ", 1);
	return (1);
}

static int	ft_printf_plus(void)
{
	write(1, "+", 1);
	return (1);
}

static int	ft_printf_hashtag(char flag)
{
	if (flag == 'x')
		write(1, "0x", 2);
	else
		write(1, "0X", 2);
	return (2);
}

int	ft_flag_handler(t_flags flags, char c)
{
	int	bytes;

	bytes = 0;
	if (flags.hashtag == 1)
		bytes = bytes + ft_printf_hashtag(c);
	if (c == '+')
	{
		if (flags.plus == 1 && flags.space == 1)
			bytes = bytes + ft_printf_plus();
		else if (flags.plus == 1)
			bytes = bytes + ft_printf_plus();
		else if (flags.space == 1)
			bytes = bytes + ft_printf_space();
	}
	return (bytes);
}
