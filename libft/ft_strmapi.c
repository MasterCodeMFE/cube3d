/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:58:42 by igcastil          #+#    #+#             */
/*   Updated: 2024/11/11 10:31:26 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Applies the function ’f’ to each character of the string ’s’ to 
 * 			create a new string (with malloc(3)) resulting from successive
 * 			applications of ’f’.
 * @param	char const * The string on which to iterate
 * @param	char (*f)(unsigned int, char) The function to apply to each character
 * @return	char * The string created from the successive applications of ’f’.
 * 			Returns NULL if the allocation fails.
 */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (!s || !f)
		return (0);
	str = ft_strdup(s);
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		str[i] = f(i, str[i]);
		i++;
	}
	return (str);
}
