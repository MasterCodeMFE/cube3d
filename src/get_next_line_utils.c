/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:50:55 by igcastil          #+#    #+#             */
/*   Updated: 2024/11/12 12:54:27 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	strlen;

	strlen = 0;
	while (s[strlen] != 0)
		strlen++;
	return (strlen);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char			*concstr;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	concstr = (char *) malloc (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
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

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!dest && !src && n != 0)
		return ((void *)0);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strchr_gnl(char *s, int c)
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

char	*ft_strdup_gnl(char *s)
{
	char	*dup;

	dup = (char *) malloc (ft_strlen_gnl(s) + 1);
	if (!dup)
		return (0);
	return (ft_memcpy_gnl((void *)dup, (const void *)s, ft_strlen_gnl(s) + 1));
}
