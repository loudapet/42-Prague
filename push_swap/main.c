/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:43:48 by plouda            #+#    #+#             */
/*   Updated: 2023/03/06 10:13:20 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_clist	*create_stack_a(int argc, const char **argv, int flag)
{
	t_clist	*stack_a;
	int	value;
	int	i;

	i = 1;
	if (flag == 1)
		i = 0;
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

char	**parse_args(char *str)
{
	char	**args;

	args = ft_split(str, ' ');
	return (args);
}

int	count_args(const char **args)
{
	int	i;

	i = 0;
	while (args[i] != 0)
		i++;
	return (i);
}

int	is_sorted(t_clist *stack)
{
	while (stack->next->next->start != 1)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	main(int argc, const char **argv)
{
	t_clist		*stack_a;
	t_clist		*stack_b;
	char		**args;
	int			flag;

	flag = 0;
	if (argc == 1)
		exit(EXIT_SUCCESS);
	if (argc == 2)
	{
		args = parse_args((char *)argv[1]);
		flag = 1;
		stack_a = create_stack_a(count_args((const char **)args), (const char **)args, flag);
	}
	else
		stack_a = create_stack_a(argc, argv, flag);
	stack_b = create_stack_b();
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
		//print_clist_a(stack_a);
		//print_clist_b(stack_b);
	}
	free_stack(&stack_a);
	free_stack(&stack_b);
	return (0);
}
