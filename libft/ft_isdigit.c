/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:26:31 by igcastil          #+#    #+#             */
/*   Updated: 2023/12/08 17:53:06 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	checks if an ascii char is a digit (0 to 9)
 * @param	int must have the value of an unsigned char which is converted to
 * 			ascii
 * @return	int zero if false, non zero if true
 * @libc	<ctype.h>
 */
int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}
