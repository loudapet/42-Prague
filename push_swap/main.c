/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:43:48 by plouda            #+#    #+#             */
/*   Updated: 2023/02/27 14:57:21 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_clist	*create_stack_a(int argc, const char **argv)
{
	t_clist	*stack_a;
	int	value;
	int	i;

	i = 1;
	value = ft_atoi(argv[i++]);
	stack_a = ft_clstnew(value);
	ft_printf("Contents of starting node A: %i\n", stack_a->value);
	stack_a->start = 1;
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		ft_clstadd_back(&stack_a, ft_clstnew(value));
		i++;
	}
	ft_clstlast(stack_a)->next = stack_a;
	ft_cprev_set(stack_a);
	return (stack_a);
}

t_clist	*create_stack_b(void)
{
	t_clist	*stack_b;
	int	value;

	value = 0;
	stack_b = ft_clstnew(value);
	ft_printf("Contents of starting node B: %i\n", stack_b->value);
	stack_b->start = 0;
	return (stack_b);
}


int	main(int argc, const char **argv)
{
	t_clist		*stack_a;
	t_clist		*stack_b;

	if (argc == 1)
		exit(EXIT_SUCCESS);
	ft_printf("%s", "\n_________TESTING-PROGRAM_________\n");
	stack_a = create_stack_a(argc, argv);
	stack_b = create_stack_b();
	ft_printf("Initial size of clist: %d\n\n", ft_clstsize_flag(stack_a));
	print_clist(stack_a);
	print_clist(stack_b);
	swap_a(stack_a);
	print_clist_swap(stack_a);
	swap_a(stack_a);
	print_clist_rev(stack_a);
	swap_a(stack_a);
	print_clist_rev_swap(stack_a);
	swap_a(stack_a);
	rotate_a(stack_a);
	print_clist_rotated(stack_a);
	reverse_rotate_a(stack_a);
	reverse_rotate_a(stack_a);
	print_clist_rev_rotated(stack_a);

	return (0);
}
