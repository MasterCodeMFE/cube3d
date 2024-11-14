/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 10:37:07 by igcastil          #+#    #+#             */
/*   Updated: 2023/12/08 17:56:30 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	copies n bytes from memory area src to memory area dest. The memory 
 * 			areas may overlap: copying takes place as though the bytes in src a
 * 			are first copied into a temporary array that does not overlap src or
 * 			dest and the bytes are then copied from the temporary array to dest.
 * @param	void* dest memory area to be written
 * @param	const void *src memory area to be read
 * @param	size_t n number of bytes to be written
 * @return	void * pointer to the memory area dest
 * @libc	<string.h>
 */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (((unsigned long int)dest - (unsigned long int)src) <= 0
		|| ((unsigned long int)dest - (unsigned long int)src) >= n)
		ft_memcpy(dest, src, n);
	else
	{
		while (n != 0)
		{
			((unsigned char *)dest)[n - 1] = ((unsigned char *)src)[n - 1];
			n--;
		}
	}
	return (dest);
}

/* int	main(void)
{
	char *src = "que pasa capullo";
	char dest[10];

	ft_memmove((void *)dest, (const void *)src, 10);
	return (0);
} COMPILA*/