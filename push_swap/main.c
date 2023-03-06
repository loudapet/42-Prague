/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:43:48 by plouda            #+#    #+#             */
/*   Updated: 2023/03/06 16:40:57 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_clist	*args_as_int(const char **argv, int argc, int flag)
{
	t_clist	*stack_a;

	if (check_int((char **)argv, flag) == 0
		|| check_minmax((char **)argv, flag) == 0)
	{
		print_error();
		exit(EXIT_FAILURE);
	}
	stack_a = create_stack_a(argc, argv, flag);
	return (stack_a);
}

t_clist	*args_as_str(const char **argv, int flag)
{
	char	**args;
	int		args_c;
	t_clist	*stack_a;

	flag = 0;
	args = parse_args((char *)argv[1]);
	if (check_int(args, flag) == 0
		|| check_minmax(args, flag) == 0)
	{
		print_error();
		free_args(args);
		exit(EXIT_FAILURE);
	}
	args_c = count_args((char **)args);
	stack_a = create_stack_a(args_c, (const char **)args, flag);
	free_args(args);
	return (stack_a);
}

void	controller(t_clist **stack_a, t_clist **stack_b)
{
	if (check_duplicates(*stack_a) == 0)
	{
		print_error();
		free_stack(stack_a);
		free_stack(stack_b);
		exit(EXIT_FAILURE);
	}
	if (ft_clstsize_flag(*stack_a) == 2)
	{
		if ((*stack_a)->value > (*stack_a)->next->value)
			swap_a(*stack_a);
	}
	else if (ft_clstsize_flag(*stack_a) == 3)
		sort_3(*stack_a);
	else if (is_sorted(*stack_a) == 0 && ft_clstsize_flag(*stack_a) > 3)
	{
		push_b(stack_a, stack_b);
		push_b(stack_a, stack_b);
		push_value(stack_a, stack_b);
		if (ft_clstsize_flag(*stack_a) == 3)
			sort_3(*stack_a);
		push_value_back(stack_a, stack_b);
		rotate_lowest_up(stack_a);
	}
}

int	main(int argc, const char **argv)
{
	t_clist		*stack_a;
	t_clist		*stack_b;
	int			flag;

	flag = 1;
	if (argc == 1)
		exit(EXIT_SUCCESS);
	else if (argc == 2)
		stack_a = args_as_str(argv, flag);
	else
		stack_a = args_as_int(argv, argc, flag);
	stack_b = create_stack_b();
	controller(&stack_a, &stack_b);
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
