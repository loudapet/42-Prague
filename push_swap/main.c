/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:43:48 by plouda            #+#    #+#             */
/*   Updated: 2023/03/06 14:37:50 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_clist	*create_stack_a(int argc, const char **argv, int flag)
{
	t_clist	*stack_a;
	int	value;
	int	i;

	i = flag;
	value = ft_atoi(argv[i++]);
	stack_a = ft_clstnew(value);
	stack_a->start = 1;
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		ft_clstadd_back(&stack_a, ft_clstnew(value));
		i++;
	}
	ft_clstlast(stack_a)->next = stack_a;
	while (stack_a->next->prev == NULL)
	{
		stack_a->next->prev = stack_a;
		stack_a = stack_a->next;
	}
	return (stack_a);
}

t_clist	*create_stack_b(void)
{
	t_clist	*stack_b;

	stack_b = ft_clstnew(0);
	stack_b->start = 0;
	return (stack_b);
}

void	free_stack(t_clist **stack)
{
	t_clist	*next;
	t_clist	*tmp;

	if (stack && *stack)
	{
		next = (*stack)->next;
		while (next && (next != *stack))
		{
			tmp = next;
			next = next->next;
			free(tmp);
		}
		free(*stack);
		*stack = NULL;
	}
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != 0)
		i++;
	return (i);
}

void	free_args(char **args)
{
	int	i;
	int	size;

	i = 0;
	size = count_args(args);
	while (i < size)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	**parse_args(char *str)
{
	char	**args;

	args = ft_split(str, ' ');
	return (args);
}

int	is_sorted(t_clist *stack)
{
	while (stack->next->start != 1)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	check_int(char **args, int flag)
{
	int	i;
	int	j;
	int	size;

	i = flag;
	size = count_args(args);
	while (i < size)
	{
		j = 0;
		while (args[i][j] != 0)
		{
			if (ft_isdigit(args[i][j]) == 0 && args[i][j] != '-')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_minmax(char **args, int flag)
{
	int	i;
	int	size;
	long	value;

	i = flag;
	size = count_args(args);
	while (i < size)
	{
		value = ft_atoi_long(args[i]);
		if (value > INT_MAX || value < INT_MIN)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_duplicates(t_clist *stack_a)
{
	int	value;
	int	counter;

	stack_a = stack_a->next;
	while (stack_a->start != 1)
	{	
		counter = 0;
		value = stack_a->value;
		while (stack_a->start != 1)
		{
			if (stack_a->next->value == value)
				return (0);
			stack_a = stack_a->next;
			counter++;
		}
		if (counter == 1)
			break ;
		while (counter > 1)
		{
			stack_a = stack_a->prev;
			counter--;
		}
	}
	return (1);
}

t_clist	*args_as_int(const char **argv, int argc, int flag)
{
	t_clist	*stack_a;

	if (check_int((char **)argv, flag) == 0 || check_minmax((char **)argv, flag) == 0)
	{
		print_error();
		exit(EXIT_FAILURE);
	}
	stack_a = create_stack_a(argc, argv, flag);
	return (stack_a);
}

t_clist	*args_as_str(const char **argv, int flag)
{
	char		**args;
	t_clist		*stack_a;

	flag = 0;
	args = parse_args((char *)argv[1]);
	if (check_int(args, flag) == 0 || check_minmax(args, flag) == 0)
	{
		print_error();
		free_args(args);
		exit(EXIT_FAILURE);
	}
	stack_a = create_stack_a(count_args((char **)args), (const char **)args, flag);
	free_args(args);
	return (stack_a);
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
	if (check_duplicates(stack_a) == 0)
	{
		print_error();
		free_stack(&stack_a);
		free_stack(&stack_b);
		exit(EXIT_FAILURE);
	}
	if (ft_clstsize_flag(stack_a) == 1)
	{
		free_stack(&stack_a);
		free_stack(&stack_b);
		exit(EXIT_SUCCESS);
	}
	else if (ft_clstsize_flag(stack_a) == 2)
	{
		if (stack_a->value > stack_a->next->value)
			swap_a(stack_a);
		free_stack(&stack_a);
		free_stack(&stack_b);
		exit(EXIT_SUCCESS);
	}
	else if (ft_clstsize_flag(stack_a) == 3)
			sort_3(stack_a);
	else if (is_sorted(stack_a) == 0)
	{
		push_b(&stack_a, &stack_b);
		push_b(&stack_a, &stack_b);
		push_value(&stack_a, &stack_b);
		if (ft_clstsize_flag(stack_a) == 3)
			sort_3(stack_a);
		push_value_back(&stack_a, &stack_b);
		rotate_lowest_up(&stack_a);
		// print_clist_a(stack_a);
		// print_clist_b(stack_b);
	}
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
