/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 09:51:31 by igcastil          #+#    #+#             */
/*   Updated: 2023/09/15 13:50:10 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Allocates memory with malloc and returns a substring from the string
 * 			s. The substring begins at index start and is of maximum size len.
 * @param	char const *s string from which to create the substring
 * @param	unsigned int start start index of the substring in the string ’s’
 * @param	size_t len maximum length of the substring
 * @return	char * pointer to substring. NULL if the allocation fails
 */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	i = 0;
	if (!s)
		return (0);
	if ((ft_strlen(s) == 0) || (start >= ft_strlen(s)))
	{
		substr = (char *) malloc (1);
		if (!substr)
			return (0);
		*substr = '\0';
		return (substr);
	}
	if ((ft_strlen(s) - start) > len)
		substr = (char *) malloc (len + 1);
	else
		substr = (char *) malloc (ft_strlen(s) - start + 1);
	if (!substr)
		return (0);
	while (start < ft_strlen(s) && i < len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
