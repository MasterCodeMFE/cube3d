/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:21:08 by igcastil          #+#    #+#             */
/*   Updated: 2023/09/18 11:21:15 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	counts number of nodes in a list
 * @param	t_list *lst pointer to first node of the list
 * @return	int nodes count.
 */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	num_nodes;

	num_nodes = 0;
	while (lst)
	{
		num_nodes++;
		lst = lst->next;
	}
	return (num_nodes);
}
