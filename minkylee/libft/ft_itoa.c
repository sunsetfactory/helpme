/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:30:12 by minkylee          #+#    #+#             */
/*   Updated: 2023/04/07 10:31:32 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_of_digits(int n)
{
	int	cnt;

	cnt = 0;
	if (n < 0)
		cnt++;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		cnt++;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	int		digit;
	char	*str;

	digit = num_of_digits(n);
	str = (char *)malloc(sizeof(char) * (digit + 1));
	if (!str)
		return (NULL);
	str[digit--] = '\0';
	if (n < 0)
	{
		str[digit--] = (n % 10) * -1 + '0';
		n = (n / 10) * -1;
		str[0] = '-';
	}
	else if (n == 0)
	{
		str[0] = '0';
	}
	while (n > 0)
	{
		str[digit--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
