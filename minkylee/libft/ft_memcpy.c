/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:41:51 by minkylee          #+#    #+#             */
/*   Updated: 2023/04/07 10:31:53 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*source;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst == src)
		return (dst);
	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	while (n-- > 0)
		*dest++ = *source++;
	return (dst);
}
