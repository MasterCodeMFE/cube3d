/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:17:19 by igcastil          #+#    #+#             */
/*   Updated: 2024/01/29 09:59:02 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	iterates through list 'lst' and applies function 'f' on each node´s
 * 			content. Creates a new list as a result of correct call of function 
 * 			’f’ on each node. ’del’ function is used to delete a node´s content 
 * 			if needed.
 * @param	t_list *lst pointer to first node of lst
 * @param	void *(*f)(void*) pointer to function to apply to each node
 *			¡¡¡OJO!!!esta función f reserva memoria para el puntero que devuelve
 *			(hay q liberarla si falla en algun momento la repliicacion de la 
 			lista)
 * @param	void (*del)(void*) pointer to function to delete a node´s content if
 * 			needed.
 * @return	t_list * pointer to list created or NULL if malloc fails
 */
#include "libft.h"

static void	clean_exit(int count, void *contnt, void (*d)(void *), t_list *lst)
{
	d(contnt);
	if (count > 0)
		ft_lstclear(&lst, d);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	void	*f_result;
	int		node_count;

	if (!lst || !f)
		return (0);
	node_count = 0;
	while (lst)
	{
		f_result = f(lst->content);
		new_node = ft_lstnew(f_result);
		if (!new_node)
		{
			clean_exit(node_count, f_result, del, new_list);
			return (0);
		}
		if (node_count == 0)
			new_list = new_node;
		else
			ft_lstadd_back(&new_list, new_node);
		node_count++;
		lst = lst->next;
	}
	return (new_list);
}
