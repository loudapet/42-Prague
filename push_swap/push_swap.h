/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:49:15 by plouda            #+#    #+#             */
/*   Updated: 2023/03/02 22:47:11 by plouda           ###   ########.fr       */
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
	int				value;
	int				start;
}				t_clist;

typedef struct	s_count
{
	int		rota_a;
	int		rota_b;
	int		rev_rota_a;
	int		rev_rota_b;
	int		rot;
	int		rev_rot;
	int		diff_a_b;
	int		diff_b_a;
	int		fin_rot;
	int		fin_diff;
	char	flag_rot_diff;
	char	flag_rev_rot_a_b;
}				t_count;


// Operations
void	swap(t_clist *stack);
void	rotate(t_clist *stack);
void	reverse_rotate(t_clist *stack);
void	push(t_clist **src, t_clist **dest);

// Sub-operations
void	swap_a(t_clist *stack_a);
void	swap_b(t_clist *stack_b);
void	swap_both(t_clist *stack_a, t_clist *stack_b);
void	rotate_a(t_clist *stack_a);
void	rotate_b(t_clist *stack_b);
void	rotate_both(t_clist *stack_a, t_clist *stack_b);
void	reverse_rotate_a(t_clist *stack_a);
void	reverse_rotate_b(t_clist *stack_b);
void	reverse_rotate_both(t_clist *stack_a, t_clist *stack_b);
void	push_a(t_clist **stack_a, t_clist **stack_b);
void	push_b(t_clist **stack_a, t_clist **stack_b);

// Counting functions
t_count	count_moves(t_clist *stack_a, t_clist *stack_b, int value_a, int value_b);
int		count_rota(t_clist *stack, int value);
int		count_rev_rota(t_clist *stack, int value);
t_count	count_diff(t_count count);
t_count	resolve_rot_diff(t_count count);
t_count	resolve_rev_rot(t_count count);
t_count	resolve_a_b(t_count count);

// Pushing correct value
int	push_above_nbr(t_clist *stack_b, int value_a);
int	get_cheapest_nbr(t_clist *stack_a, t_clist *stack_b);

// Counting utils
t_count	init_count(int rota_a, int rota_b, int rev_rota_a, int rev_rota_b);
int		max_value(t_clist *stack);
int		min_value(t_clist *stack);

// Testing functions
void	print_clist_a(t_clist *stack);
void	print_clist_b(t_clist *stack);
void	print_clist_rev(t_clist *stack);
void	print_clist_swap(t_clist *stack);
void	print_clist_rev_swap(t_clist *stack);
void	print_clist_rotated(t_clist *stack);
void	print_clist_rev_rotated(t_clist *stack);

// Utils
int		ft_clstsize(t_clist *lst);
t_clist	*ft_clstlast(t_clist *lst);
void	ft_clstadd_back(t_clist **lst, t_clist *new);
t_clist	*ft_clstnew(int value);
int		ft_clstsize_flag(t_clist *lst);
t_clist	*ft_clstlast_flag(t_clist *lst);
void	ft_clstadd_front(t_clist **lst, t_clist *new);

#endif