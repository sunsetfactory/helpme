/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:38:50 by minkylee          #+#    #+#             */
/*   Updated: 2023/04/07 10:31:21 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_num(const char *str, int sign)
{
	const char	*s;
	long long	rst;
	int			i;

	s = str;
	rst = 0;
	i = 0;
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		rst = rst * 10 + (s[i] - '0');
		if (rst >= 922337203685477580 && (s[i + 1] >= '0' && s[i + 1] <= '9'))
		{
			if (rst == 922337203685477580 && s[i + 1] < '8' && sign == 1)
				return (1);
			else if (rst == 922337203685477580 && s[i + 1] < '9' && sign == -1)
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	rst;

	sign = 1;
	rst = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	if (!check_num(str, sign))
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		rst = rst * 10 + (*str - '0');
		str++;
	}
	return (sign *(int)(rst));
}
