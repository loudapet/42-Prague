/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:56:24 by plouda            #+#    #+#             */
/*   Updated: 2023/02/03 14:48:16 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdio.h>

// cc -Wall -Wextra -Werror -o ft_printf ft_printf_char.c ft_printf_hex.c ft_printf_nbr.c ft_printf_str.c ft_printf_unbr.c ft_printf.c ft_uitoa.c libft.a main.c

int	main (void)
{
	ft_printf("I am a char test: %c\n", 'q');
	printf("I am a char test: %c\n", 'q');

	ft_printf("I am a str test: %s\n", "string");
	printf("I am a str test: %s\n", "string");

	ft_printf("I am a decimal/int test: %d %i\n", -10, 20);
	printf("I am a decimal/int test: %d %i\n", -10, 20);

	ft_printf("I am an unsigned int test: %u\n", 50);
	printf("I am an unsigned int test: %u\n", 50);

	ft_printf("I am a hexa test: %x\n", 540);
	printf("I am a hexa test: %x\n", 540);

	ft_printf("I am a hexa test: %X\n", 540);
	printf("I am a hexa test: %X\n", 540);

	ft_printf("I am a percent test: %%\n");
	printf("I am a percent test: %%\n");

	return 0;
}