/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:30:51 by igcastil          #+#    #+#             */
/*   Updated: 2023/12/08 17:58:01 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	checks whether c is a 7-bit unsigned char value that fits into the
 * 			ASCII character set (0 to 127 ¡¡¡not the extended ascii!!!!)
 * @param	int must have the value of an unsigned char which is converted to
 * 			ascii
 * @return	int zero if false, non zero if true
 * @libc	<ctype.h>
 */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
