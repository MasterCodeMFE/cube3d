/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:21:23 by igcastil          #+#    #+#             */
/*   Updated: 2023/09/19 11:03:07 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Creates a new node using malloc(3). member variable ’content’ is
 * 			initialized with ’content’ parameter. The ’next’ variable is set to
 * 			NULL.
 * @param	void *content of node created
 * @return	t_list * pointer to node created.
 */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *) malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->content = content;
	new_node->next = (t_list *)0;
	return (new_node);
}
