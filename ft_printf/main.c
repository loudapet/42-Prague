/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:56:24 by plouda            #+#    #+#             */
/*   Updated: 2023/02/02 08:37:02 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdio.h>

// cc -Wall -Wextra -Werror -o ft_printf ft_printf_char.c ft_printf_hex.c ft_printf_nbr.c ft_printf_str.c ft_printf_unbr.c ft_printf.c ft_uitoa.c libft.a main.c

int	main (void)
{
	//int	bytes;

	//char	*str1 = "I am a test\n";
	//char	*str2 = "You are another test\n";
	//char	*str3 = "join me";
	//char	*str4 = NULL;
	
	//ft_printf(str1);
	//ft_printf(str2);
	//printf("Hello, %s in my sleep\n", str3);

	//bytes = printf("Empty%s\n", str4);
	//printf("Bytes printed: %i", bytes);

	//ft_printf_unbr(42903275);
	//printf("I am 540 in hexadecimal: %x\n", 540);
	ft_printf_hex(540);

	return 0;
}