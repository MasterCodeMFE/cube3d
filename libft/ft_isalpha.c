/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:05:07 by igcastil          #+#    #+#             */
/*   Updated: 2023/12/08 17:54:36 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	checks if an ascii char is alphabetic (a to z or A to Z)
 * 			same as isupper(c) || islower(c)			
 * @param	int must have the value of an unsigned char which is converted to
 * 			ascii
 * @return	int zero if false, non zero if true
 * @libc	<ctype.h>
 */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
