/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:43:48 by plouda            #+#    #+#             */
/*   Updated: 2023/02/24 10:44:27 by plouda           ###   ########.fr       */
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
	ft_printf("Contents of starting node: %i\n", stack_a->value);
	stack_a->start = 1;
	while (i < argc)
	{
		value = ft_atoi(argv[i]);
		ft_clstadd_back(&stack_a, ft_clstnew(value));
		i++;
	}
	//ft_clstlast(stack_a)->next = stack_a;
	return (stack_a);
}

int	main(int argc, const char **argv)
{
	int		i;
	t_clist		*stack_a;

	i = 1;
	if (argc == 1)
		exit(EXIT_SUCCESS);
	stack_a = create_stack_a(argc, argv);
	ft_printf("Size of list: %d\n", ft_clstsize(stack_a));
	i = 1;
	while (stack_a)
	{
		ft_printf("Contents of node %d: %i\n", i, stack_a->value);
		ft_printf("Start of node %d: %i\n", i++, stack_a->start);
		stack_a = stack_a->next;
	}
	return (0);
}
