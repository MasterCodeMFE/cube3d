/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 23:29:04 by igcastil          #+#    #+#             */
/*   Updated: 2023/09/21 10:41:43 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	allocates memory for an array of nmemb elements of size bytes each 
 * 			and returns a pointer to the allocated memory. The memory is set to 
 * 			zero. If nmemb or size is 0, then calloc() returns either NULL, or a
 * 			unique pointer value that can later be successfully passed to free().
 * @param	size_t nmemb number of elements to be allocated
 * @param	size_t size in bytes of each element
 * @return	void * pointer to the allocated memory. If nmemb or size is 0, then 
 * 			returns either NULL, or a pointer that can later be successfully
 * 			passed to free().
 * @libc	<stdlib.h>
 */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc (nmemb * size);
	if (!ptr)
		return (0);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
