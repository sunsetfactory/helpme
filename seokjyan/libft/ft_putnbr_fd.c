/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 23:02:12 by minkylee          #+#    #+#             */
/*   Updated: 2023/04/07 10:31:59 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print(int nb, int fd)
{
	char	a[2];

	if (nb == 0)
	{
		return ;
	}
	else if (nb > 0)
	{
		a[0] = (nb % 10) + '0';
		print(nb / 10, fd);
		write(fd, &a, 1);
	}
	else if (nb < 0)
	{
		write (fd, "-", 1);
		a[0] = (-nb % 10) + '0';
		print(-nb / 10, fd);
		write(fd, &a, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n == 0)
	{
		write(fd, "0", 1);
	}
	else
	{
		print(n, fd);
	}
}
