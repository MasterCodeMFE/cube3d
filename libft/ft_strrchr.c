/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:05:51 by igcastil          #+#    #+#             */
/*   Updated: 2023/12/08 17:49:12 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	returns a pointer to last occurrence of the character c in the 
 * 			string s. Terminating null character is considered to be part of the
 * 			string, therefore if c is `\0', returns pointer to terminating `\0'.
 * @param	char* s parsed string
 * @param	int must have the value of an unsigned char which is converted to 
 * 			ascii
 * @return	char* pointer to the last occurrence of the character c. If the value
 * 			is not found, the function returns a null pointer
 * @libc	<string.h>
 */

char	*ft_strrchr(const char *s, int c)
{
	const char	*initial_pointer;

	initial_pointer = s;
	while (*s != '\0')
		s++;
	while (s != initial_pointer)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s--;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (0);
}
