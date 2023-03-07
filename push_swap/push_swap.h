/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:49:15 by plouda            #+#    #+#             */
/*   Updated: 2023/03/07 13:05:10 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libftprintf/ft_printf.h"
# include <stdlib.h>
# include <limits.h>

typedef struct s_clist
{
	struct s_clist	*next;
	struct s_clist	*prev;
	int				value;
	int				start;
}				t_clist;

typedef struct s_count
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

typedef struct s_values
{
	int	value_a;
	int	value_b;
}				t_values;

// Create stacks
t_clist		*create_stack_a(int argc, const char **argv, int flag);
t_clist		*create_stack_b(void);

// Operations
void		swap(t_clist *stack);
void		rotate(t_clist *stack);
void		reverse_rotate(t_clist *stack);
void		push(t_clist **src, t_clist **dest);

// Sub-operations
void		swap_a(t_clist *stack_a);
void		swap_b(t_clist *stack_b);
void		swap_both(t_clist *stack_a, t_clist *stack_b);
void		rotate_a(t_clist *stack_a);
void		rotate_b(t_clist *stack_b);
void		rotate_both(t_clist *stack_a, t_clist *stack_b);
void		reverse_rotate_a(t_clist *stack_a);
void		reverse_rotate_b(t_clist *stack_b);
void		reverse_rotate_both(t_clist *stack_a, t_clist *stack_b);
void		push_a(t_clist **stack_a, t_clist **stack_b);
void		push_b(t_clist **stack_a, t_clist **stack_b);

// Counting functions
t_count		count_moves(t_clist *st_a, t_clist *st_b, int val_a, int val_b);
t_count		count_diff(t_count count);
t_count		resolve_rot_diff(t_count count);
t_count		resolve_rev_rot(t_count count);
t_count		resolve_a_b(t_count count);

// Counting utils
t_count		init_count(int rota_a, int rota_b, int rev_rota_a, int rev_rota_b);
int			max_value(t_clist *stack);
int			min_value(t_clist *stack);
int			count_rota_a(t_clist *stack);
int			count_rev_rota_a(t_clist *stack);
int			count_rota_b(t_clist *stack, int value);
int			count_rev_rota_b(t_clist *stack, int value);

// Get cheapest number
int			get_cheapest_nbr(t_clist *stack_a, t_clist *stack_b);
int			get_cost(t_count count);
t_values	get_values(t_clist *stack_a, t_clist *stack_b);

// Pushing functions and final sort
void		push_value(t_clist **stack_a, t_clist **stack_b);
int			push_above_nbr(t_clist *stack_b, int value_a);
void		push_value_back(t_clist **stack_a, t_clist **stack_b);
int			push_above_nbr_a(t_clist *stack_a, int value_b);
void		rotate_lowest_up(t_clist **stack_a);
void		flag_a(t_clist *stack_a, t_clist *stack_b, t_count count);
void		flag_b(t_clist *stack_a, t_clist *stack_b, t_count count);
void		flag_c(t_clist *stack_a, t_clist *stack_b, t_count count);
void		flag_d(t_clist *stack_a, t_clist *stack_b, t_count count);

// Sort 3 numbers
void		sort_3(t_clist *stack);

// Validators
int			check_int(char **args, int flag);
int			check_minmax(char **args, int flag);
int			check_duplicates(t_clist *stack_a);
int			is_sorted(t_clist *stack);

// Circular linked list utils
t_clist		*ft_clstnew(int value);
t_clist		*ft_clstlast(t_clist *lst);
void		ft_clstadd_front(t_clist **lst, t_clist *new);
void		ft_clstadd_back(t_clist **lst, t_clist *new);
int			ft_clstsize(t_clist *lst);
int			ft_clstsize_flag(t_clist *lst);

// Utils
long		ft_atoi_long(const char *nptr);
int			count_args(char **args);
char		**parse_args(char *str);
void		free_args(char **args);
void		free_stack(t_clist **stack);

// Testing functions
void		print_clist_a(t_clist *stack);
void		print_clist_b(t_clist *stack);

// Error
void		print_error(void);

#endif