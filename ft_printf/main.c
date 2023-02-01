/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:56:24 by plouda            #+#    #+#             */
/*   Updated: 2023/02/01 11:38:14 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdio.h>

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
	printf("I am 184 in hexadecimal: %x\n", 184);
	write(1, "\n", 1);

	return 0;
}