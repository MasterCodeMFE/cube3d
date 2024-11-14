/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 18:40:45 by igcastil          #+#    #+#             */
/*   Updated: 2023/08/25 18:53:59 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	compares the first n bytes (each interpreted as unsigned char) of 
 * 			the memory areas s1 and s2.
 * @param	const void *s1 memory area to be compared
 * @param	const void *s2 memory area to be compared
 * @param	size_t n maximum number of bytes to be compared
 * @return	int difference between the first pair of bytes (interpreted as
 * 			unsigned char) that differ in s1 and s2.
 * @libc	<string.h>
 */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	if (i == n)
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
