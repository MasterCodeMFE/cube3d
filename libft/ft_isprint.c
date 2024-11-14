/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 10:43:16 by igcastil          #+#    #+#             */
/*   Updated: 2024/01/29 09:58:36 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	checks for any printable character including space (codes 32 to 126)
 * @param	int must have the value of an unsigned char which is converted to 
 * 			ascii
 * @return	int zero if false, non zero if true
 * @libc	<ctype.h>
 */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
