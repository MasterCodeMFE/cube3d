/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 10:48:15 by igcastil          #+#    #+#             */
/*   Updated: 2023/08/26 11:30:00 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Allocates with malloc and returns a new string, which is the result
 * 			of the concatenation of ’s1’ and ’s2’
 * @param	char const * prefix string
 * @param	char const * suffix string.
 * @return	char * The new string. NULL if the allocation fails.
 */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*concstr;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	concstr = (char *) malloc (ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!concstr)
		return (0);
	while (s1[i] != '\0')
	{
		concstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		concstr[i++] = s2[j++];
	concstr[i] = '\0';
	return (concstr);
}
