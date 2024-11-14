/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:23:36 by igcastil          #+#    #+#             */
/*   Updated: 2023/10/02 16:14:58 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	locates the first occurrence of the null-terminated string little in
 * 			the string big, where not more than len characters are searched.
 * 			Characters that appear after a '\0' character are not searched.
 * @param	char* big haystack string
 * @param	char* little needle string
 * @param	size_t len maximum number of bytes searched in big string
 * @return	char	* If little is an empty string, big is returned; if little
 * 			occurs nowhere in big, NULL is returned; otherwise a pointer to the
 * 			first character of the first occurrence of little is returned.
 * @libc	<string.h>
 */

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	l;

	b = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[b] != '\0')
	{
		l = 0;
		while (big[b + l] == little[l] && (b + l) < len)
		{
			if (little[l] == '\0')
				return ((char *)(big + b));
			l++;
		}
		if (little[l] == '\0')
			return ((char *)(big + b));
		b++;
	}
	return (0);
}
