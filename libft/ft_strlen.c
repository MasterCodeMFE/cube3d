/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:09:33 by igcastil          #+#    #+#             */
/*   Updated: 2024/01/29 09:59:43 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	calculate the length of a string excluding terminating null byte 
 * 			('\0')
 * @param	char* string whose length is to be measured
 * @return	size_t number of bytes in the string
 * @libc	<string.h>
 */

// size_t is an unsigned integral data type which is defined in various header
// files such as:<stddef.h>, <stdio.h>, <stdlib.h>, <string.h>, <time.h>, ...
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	strlen;

	strlen = 0;
	while (s[strlen] != 0)
		strlen++;
	return (strlen);
}
