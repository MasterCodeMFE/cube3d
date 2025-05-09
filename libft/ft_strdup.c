/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 00:00:45 by igcastil          #+#    #+#             */
/*   Updated: 2023/08/26 00:18:50 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	returns a pointer to a new string which is a duplicate of the string
 * 			s. Memory for the new string is obtained with malloc.
 * @param	const char* string to duplicate
 * @return	pointer to a new string which is a duplicate of the string s
 * @libc	<string.h>
 */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = (char *) malloc (ft_strlen(s) + 1);
	if (!dup)
		return (0);
	return (ft_memcpy((void *)dup, (const void *)s, ft_strlen(s) + 1));
}

/* int	main(void)
{
	const char *src = "que pasa capullo";
	ft_strdup(src);
	return (0);
} COMPILA*/