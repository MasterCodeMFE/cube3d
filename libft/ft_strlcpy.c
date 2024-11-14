/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:20:11 by igcastil          #+#    #+#             */
/*   Updated: 2023/10/20 18:30:25 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	copies up to dst_length - 1 characters from the NUL-terminated string
 * 			src to dst, NUL-terminating the result.
 * @param	char* dst written string
 * @param	char* src read string
 * @param	size_t size number of chars to be copied ('\0' included)
 * @return	size_t length of src
 * @libc	<string.h>
 */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_length)
{
	size_t	i;

	i = 0;
	if (dst_length != 0)
	{
		while (src[i] != '\0' && i < (dst_length - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
