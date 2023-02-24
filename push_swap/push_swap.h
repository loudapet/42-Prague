/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:49:15 by plouda            #+#    #+#             */
/*   Updated: 2023/02/24 10:17:17 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libftprintf/ft_printf.h"
# include <stdlib.h>

typedef struct	s_clist
{
	struct s_clist	*next;
	int		value;
	int		start;
}				t_clist;

int		ft_clstsize(t_clist *lst);
t_clist	*ft_clstlast(t_clist *lst);
void	ft_clstadd_back(t_clist **lst, t_clist *new);
t_clist	*ft_clstnew(int value);

#endif