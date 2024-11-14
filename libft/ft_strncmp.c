/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:14:16 by igcastil          #+#    #+#             */
/*   Updated: 2023/08/24 13:35:58 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	compares the first n bytes of two strings s1 and s2. It returns an 
 * 			integer less than, equal to, or greater than zero if s1 is found, to
 * 			be less than, to match, or be greater than s2.
 * @param	char* s1 compared string
 * @param	char* s2 compared string
 * @param	size_t n number of bytes to compare
 * @return	int less than, equal to, or greater than zero if s1 is found, to
 * 			be less than, to match, or be greater than s2.
 * @libc	<string.h>
 */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(s1 + i) != *(s2 + i))
			return ((int)(unsigned char)*(s1 + i) - (unsigned char)*(s2 + i));
		if (*(s1 + i) == '\0')
			return (0);
		i++;
	}
	return (0);
}
