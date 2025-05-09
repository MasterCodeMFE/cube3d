/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:47:32 by igcastil          #+#    #+#             */
/*   Updated: 2023/08/25 00:06:14 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	fills the first n bytes of the memory area pointed to by s with the 
 * 			constant byte c.
 * @param	void* s memory area pointed
 * @param	int c content to be written in memory
 * @param	size_t n number of bytes to be written
 * @return	void * pointer to the memory area s
 * @libc	<string.h>
 */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}
