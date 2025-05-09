/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 10:45:14 by igcastil          #+#    #+#             */
/*   Updated: 2023/12/08 17:50:08 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	returns a pointer to first occurrence of the character c in the 
 * 			string s. Terminating null character is considered to be part of the
 * 			string, therefore if c is `\0', returns pointer to terminating `\0'.
 * @param	char* s parsed string
 * @param	int must have the value of an unsigned char which is converted to 
 * 			ascii
 * @return	char* pointer to the first occurrence of the character c, or NULL if
 * 			the character is not found
 * @libc	<string.h>
 */

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (0);
}
