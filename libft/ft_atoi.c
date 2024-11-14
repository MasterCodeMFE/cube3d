/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 19:01:03 by igcastil          #+#    #+#             */
/*   Updated: 2023/09/10 18:01:26 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	converts the initial portion of the string pointed to by nptr to int
 * 			The string may begin with an arbitrary amount of white space (as
 *			determined by isspace(3)) followed by a single optional '+' or '-'
 * 			VERSIONS
 * 			POSIX.1 leaves the return value on error unspecified.
 * 			On glibc, musl libc, and uClibc, 0 is returned on error.
 * @param	const char* parsed string
 * @return	int converted value or 0 on error
 * @libc	<stdlib.h>
 */

int	ft_atoi(const char *nptr)
{
	int		negative_sign;
	long	result;

	negative_sign = 1;
	result = 0;
	while (*nptr == ' ' || ((*nptr >= 9) && (*nptr <= 13)))
		nptr++;
	if ((*nptr == '+') || (*nptr == '-'))
	{
		if (*nptr == '-')
			negative_sign = negative_sign * (-1);
		nptr++;
	}
	while ((*nptr >= '0') && (*nptr <= '9'))
	{
		result = (result * 10) + *nptr - '0';
		nptr++;
	}
	return ((int)(negative_sign * result));
}
