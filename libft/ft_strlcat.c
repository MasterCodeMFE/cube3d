/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 18:04:50 by igcastil          #+#    #+#             */
/*   Updated: 2023/09/15 12:42:17 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	appends the NUL-terminated string src to the end of dst. It will
 * append at most size - strlen(dst) - 1 bytes, NUL-terminating the result.
 * @param	char* dst written string
 * @param	char* src read string
 * @param	size_t size number of final chars in dst ('\0' included)
 * @return	size_t length of src + dst (src + dst_final_length if the latter is
 * 			less than dst)
 * @libc	<string.h>
 */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dst_final_length)
{
	size_t	growing_str_length;
	size_t	i;

	growing_str_length = ft_strlen(dst);
	i = 0;
	if (dst_final_length <= growing_str_length)
		return (dst_final_length + ft_strlen(src));
	while (src[i] != '\0' && growing_str_length < dst_final_length - 1)
	{
		dst[growing_str_length] = src[i];
		growing_str_length++;
		i++;
	}
	dst[growing_str_length] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
