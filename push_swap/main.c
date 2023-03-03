/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:43:48 by plouda            #+#    #+#             */
/*   Updated: 2023/03/03 12:03:46 by plouda           ###   ########.fr       */
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

int	main(int argc, const char **argv)
{
	t_clist		*stack_a;
	t_clist		*stack_b;

	if (argc == 1)
		exit(EXIT_SUCCESS);
	ft_printf("%s", "\n_________TESTING-PROGRAM_________\n");
	stack_a = create_stack_a(argc, argv);
	stack_b = create_stack_b();
	ft_printf("Initial size of A: %d\n\n", ft_clstsize_flag(stack_a));
	push_b(&stack_a, &stack_b);
	push_b(&stack_a, &stack_b);
	push_value(&stack_a, &stack_b);
	
	// ./push_swap 0 9 6 7 8 2 1 5 4 10
	// ./push_swap 38 63 39 84 30 237 843 434 948

	free_stack(&stack_a);
	free_stack(&stack_b);

	return (0);
}
