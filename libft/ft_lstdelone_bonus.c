/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:12:17 by igcastil          #+#    #+#             */
/*   Updated: 2023/09/18 12:23:39 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	frees memory of node 'lst' (and its content) using funcion 'del'
 * 			Memory of field-node lst->next must not be freed.
 * @param	t_list **lst node to be freed
 * @param	void (*del)(void*) pointer to function used to free node´s memory
 */
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
