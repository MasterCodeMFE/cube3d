/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igcastil <igcastil@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:31:41 by igcastil          #+#    #+#             */
/*   Updated: 2023/09/13 19:42:57 by igcastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief	Allocates (with malloc(3)) and returns a string representing the 
 * 			integer received as an argument. Negative numbers must be handled
 * @param	int n integer to convert.
 * @return	char * string representing the integer. NULL if the allocation fails.
 */

#include "libft.h"

static size_t	count_digits(int number)
{
	size_t	num_digits;
	long	number_cpy;

	num_digits = 0;
	number_cpy = (long) number;
	if (number == 0)
		return (1);
	if (number < 0)
		number_cpy = -number_cpy;
	while (number_cpy > 0)
	{
		num_digits++;
		number_cpy = number_cpy / 10;
	}
	return (num_digits);
}

static void	fill_str(char	*str, int number)
{
	size_t	index;
	long	number_cpy;

	number_cpy = number;
	if (number_cpy < 0)
		number_cpy = -number_cpy;
	index = count_digits(number_cpy) -1;
	if (number < 0)
		index++;
	str[index + 1] = '\0';
	while (number_cpy > 0)
	{
		str[index] = '0' + (number_cpy % 10);
		number_cpy = number_cpy / 10;
		index--;
	}
	if (number < 0)
		str[0] = '-';
	if (number == 0)
		str[0] = '0';
}

char	*ft_itoa(int n)
{
	size_t	is_negative;
	char	*str;

	is_negative = 0;
	if (n < 0)
		is_negative = 1;
	str = (char *)malloc(count_digits(n) + is_negative + 1);
	if (!str)
		return (0);
	fill_str (str, n);
	return (str);
}
