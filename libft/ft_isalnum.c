/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 01:17:51 by igcastil          #+#    #+#             */
/*   Updated: 2024/01/29 09:58:19 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	checks if an ascii char is alphanumeric (equivalent to (isalpha(c)
 * 			|| isdigit(c))
 * @param	int must have the value of an unsigned char which is converted to
 * 			ascii
 * @return	int zero if false, non zero if true
 * @libc	<ctype.h>
 */

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
