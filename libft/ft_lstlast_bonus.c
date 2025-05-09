/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:26:13 by igcastil          #+#    #+#             */
/*   Updated: 2023/09/19 13:41:15 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	returns las node of the list
 * @param	t_list *lst beginning of the list
 * @return	t_list *pointer to last node of the list.
 */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last_node;

	last_node = 0;
	while (lst)
	{
		last_node = lst;
		lst = lst->next;
	}
	return (last_node);
}
