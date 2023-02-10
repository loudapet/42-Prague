/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:01:50 by plouda            #+#    #+#             */
/*   Updated: 2023/02/10 14:44:31 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "libft/libft.h"

typedef struct s_flags
{
	int		plus;
	int		space;
	int		hashtag;
	char	specifier;
	int		count_fill;
}				t_flags;

int		ft_printf(const char *str, ...);
int		ft_printf_char(char c);
int		ft_printf_str(char *str);
int		ft_printf_nbr(int nb, t_flags flags);
int		ft_printf_unbr(unsigned int unb);
char	*ft_uitoa(unsigned int n);
int		ft_printf_hex(unsigned int unb, char flag, t_flags flags);
int		ft_printf_ptr(uintptr_t n, t_flags flags);
int		ft_flag_handler(t_flags flags, char c);

#endif