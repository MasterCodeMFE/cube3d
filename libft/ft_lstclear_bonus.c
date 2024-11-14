/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:38:29 by igcastil          #+#    #+#             */
/*   Updated: 2023/09/20 13:07:53 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	deletes and frees memory of node 'lst' and all following nodes using
 * 			functions 'del' and free. In the end pointer to lst must remain NULL
 * @param	t_list **lst node where deletion begins
 * @param	void (*del)(void*) pointer to function used to delete a node
 */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;

	if (*lst)
	{
		while (*lst)
		{
			del((*lst)->content);
			aux = (*lst)->next;
			free(*lst);
			*lst = aux;
		}
	}
}
