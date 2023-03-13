/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 09:30:46 by plouda            #+#    #+#             */
/*   Updated: 2023/03/13 14:54:55 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
When stack a and stack b are created, checks for duplicates.
If there are duplicates, frees both stacks and exits the program.
If there are no duplicates:
	If there were just two arguments, swaps their values in case
	they are not sorted, and exits successfully.
	If there were three arguments, calls function that sorts them
	in place and exits successfully.
	If there were more than three arguments to sort and they are not
	sorted, pushes two numbers from the top of stack a to stack b
	and calls push_value. When there are only three members remaining
	in stack a, sorts them and then calls push_value_back. Finally,
	when stack b is empty, rotates stack a so that the lowest value
	is located at the top of the stack.
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
	print_clist_a(*stack_a);
	print_clist_b(*stack_b);
	while (instr)
	{
		exe_instr(instr, stack_a, stack_b);
		print_clist_a(*stack_a);
		print_clist_b(*stack_b);
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
If no arguments were passed, exits successfully. If only two were passed,
handles them in the way as if they were passed in a string. If the arguments
pass all validations successfully, calls for controller which sorts
the arguments. Finally frees both stacks and exits successfully.
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