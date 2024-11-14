/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 12:18:05 by igcastil          #+#    #+#             */
/*   Updated: 2023/12/08 17:48:50 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	If c is a lowercase letter, returns its uppercase
 * 			equivalent, otherwise, it returns c
 * @param	int must have the value of an unsigned char which is converted to 
 * 			ascii
 * @return	int uppercase equivalent, otherwise, it returns c
 * @libc	<ctype.h>
 */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}
