/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 23:58:22 by igcastil          #+#    #+#             */
/*   Updated: 2023/09/15 12:25:25 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	copies n bytes from memory area src to memory area dest. The memory
 * 			areas must not overlap. Use memmove(3) if the memory areas do overlap
 * @param	void* dest memory area to be written
 * @param	const void *src memory area to be read
 * @param	size_t n number of bytes to be written
 * @return	void * pointer to the memory area dest
 * @libc	<string.h>
 */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!dest && !src && n != 0)
		return ((void *)0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
