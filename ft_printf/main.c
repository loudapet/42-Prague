/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:56:24 by plouda            #+#    #+#             */
/*   Updated: 2023/02/10 14:47:59 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdio.h>

// cc -Wall -Wextra -Werror -o ft_printf ft_printf_char.c ft_printf_hex.c ft_printf_nbr.c ft_printf_str.c ft_printf_unbr.c ft_printf_ptr.c ft_printf.c ft_uitoa.c libft.a main.c

int	main (void)
{
	int		bytes;
	int		a;
	void	*ptr;

	a = 90;
	ptr = &a;

	bytes = ft_printf("I am a char test: %c\n", 'q');
	printf("Bytes printed: %i\n", bytes);
	bytes = printf("I am a char test: %c\n", 'q');
	printf("Bytes printed: %i\n\n", bytes);

	bytes = ft_printf("I am a str test: %s\n", "string");
	printf("Bytes printed: %i\n", bytes);
	bytes = printf("I am a str test: %s\n", "string");
	printf("Bytes printed: %i\n\n", bytes);

	bytes = ft_printf("I am a decimal/int test: %d %+ + ++ i\n", -10, 20);
	printf("Bytes printed: %i\n", bytes);
	bytes = printf("I am a decimal/int test: %d %+ + ++ i\n", -10, 20);
	printf("Bytes printed: %i\n\n", bytes);

	bytes = ft_printf("I am an unsigned int test: %u\n", 50);
	printf("Bytes printed: %i\n", bytes);
	bytes = printf("I am an unsigned int test: %u\n", 50);
	printf("Bytes printed: %i\n\n", bytes);

	bytes = ft_printf("I am a small hexa test: %x\n", 0);
	printf("Bytes printed: %i\n", bytes);
	bytes = printf("I am a small hexa test: %x\n", 0);
	printf("Bytes printed: %i\n\n", bytes);

	bytes = ft_printf("I am a big hexa test: %X\n", 540);
	printf("Bytes printed: %i\n", bytes);
	bytes = printf("I am a big hexa test: %X\n", 540);
	printf("Bytes printed: %i\n\n", bytes);

	bytes = ft_printf("I am a pointer test: %p\n", ptr);
	printf("Bytes printed: %i\n", bytes);
	bytes = printf("I am a pointer test: %p\n", ptr);
	printf("Bytes printed: %i\n\n", bytes);

	bytes = ft_printf("I am a percent test: %%\n");
	printf("Bytes printed: %i\n", bytes);
	bytes = printf("I am a percent test: %%\n");
	printf("Bytes printed: %i\n\n", bytes);

	return 0;
}