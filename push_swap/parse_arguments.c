/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:49:59 by plouda            #+#    #+#             */
/*   Updated: 2023/03/13 14:50:26 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Validates and creates stack a from individually passed arguments
(e.g. ./push_swap  6 7 9 3 4 2). Exits the program if validation fails.
*/
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

/*
Validates and creates stack a from arguments passed in a string
(e.g. ./push_swap "6 7 9 3 4 2"). Exits the program if validation fails.
*/
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
