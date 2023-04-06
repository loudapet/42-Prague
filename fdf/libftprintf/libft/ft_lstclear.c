/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:32:36 by plouda            #+#    #+#             */
/*   Updated: 2023/01/20 16:26:08 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	if (!lst)
		return ;
	if (*lst && del)
	{
		current = *lst;
		while (current)
		{
			temp = current->next;
			ft_lstdelone(current, del);
			current = temp;
		}
	}
	*lst = NULL;
}
