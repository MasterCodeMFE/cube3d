/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:45:20 by igcastil          #+#    #+#             */
/*   Updated: 2023/08/25 18:00:15 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	scans the initial n bytes of the memory area pointed to by s for the
 * 			first instance of c. Both c and the bytes of the memory area pointed
 * 			to by s are interpreted as unsigned char.
 * @param	const void *s memory area to be scanned
 * @param	int c searched char
 * @param	size_t n maximum number of bytes to be scanned in s
 * @return	void * pointer to the matching byte or NULL if the character does not
 * 			occur in the given memory area.
 * @libc	<string.h>
 */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && ((unsigned char *)s)[i] != (unsigned char)c)
		i++;
	if (i == n)
		return (0);
	return ((void *)s + i);
}
