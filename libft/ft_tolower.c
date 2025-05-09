/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:26:39 by igcastil          #+#    #+#             */
/*   Updated: 2024/01/29 09:59:56 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	If c is an uppercase letter, returns its lowercase
 * 			equivalent, otherwise, it returns c
 * @param	int must have the value of an unsigned char which is converted to 
 * 			ascii
 * @return	int lowercase equivalent, otherwise, it returns c
 * @libc	<ctype.h>
 */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}
