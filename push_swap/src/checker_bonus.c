/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:30:46 by plouda            #+#    #+#             */
/*   Updated: 2023/03/13 15:25:01 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

/*
When stack a and stack b are created, checks for duplicates.
If there are duplicates, frees both stacks and exits the program.
If there are no duplicates, reads line by line on standard input,
executes the instructions (or prints error), and finally checks
whether stack a is sorted and stack b is empty.
*/
static void	controller(t_clist **stack_a, t_clist **stack_b)
{
	char	*instr;

	if (check_duplicates(*stack_a) == 0)
	{
		print_error();
		free_stack(stack_a);
		free_stack(stack_b);
		exit(EXIT_FAILURE);
	}
	instr = get_next_line(0);
	while (instr)
	{
		exe_instr(instr, stack_a, stack_b);
		free(instr);
		instr = get_next_line(0);
	}
	free(instr);
	if (((*stack_b)->value == 0 && (*stack_b)->next == NULL)
		&& is_sorted(*stack_a))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

/*
If no arguments were passed, exits successfully. If only two were 
passed, handles them in the way as if they were passed in a string.
If the arguments pass all validations successfully, calls for controller
which executes instructions and validates them. Finally frees both stacks
and exits successfully.
*/
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
