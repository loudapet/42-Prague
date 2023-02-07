/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 11:01:50 by plouda            #+#    #+#             */
/*   Updated: 2023/02/07 16:10:29 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include "libft/libft.h"

int		ft_printf(const char *str, ...);
int		ft_printf_char(char c);
int		ft_printf_str(char *str);
int		ft_printf_nbr(int nb);
int		ft_printf_unbr(unsigned int unb);
char	*ft_uitoa(unsigned int n);
int		ft_printf_hex(unsigned int unb, char flag);
int		ft_printf_ptr(uintptr_t n);

#endif