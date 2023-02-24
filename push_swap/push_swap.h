/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:49:15 by plouda            #+#    #+#             */
/*   Updated: 2023/02/24 12:27:00 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libftprintf/ft_printf.h"
# include <stdlib.h>

typedef struct	s_clist
{
	struct s_clist	*next;
	struct s_clist	*prev;
	int		value;
	int		start;
}				t_clist;

int		ft_clstsize(t_clist *lst);
t_clist	*ft_clstlast(t_clist *lst);
void	ft_clstadd_back(t_clist **lst, t_clist *new);
t_clist	*ft_clstnew(int value);
int	ft_clstsize_flag(t_clist *lst);
t_clist	*ft_clstlast_flag(t_clist *lst);
void	ft_cprev_set(t_clist *lst);
void	print_clist(t_clist *stack);
void	print_clist_rev(t_clist *stack);

#endif