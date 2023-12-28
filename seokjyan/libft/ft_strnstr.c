/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 00:33:23 by minkylee          #+#    #+#             */
/*   Updated: 2023/04/07 10:32:13 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		i = 0;
		while (*(needle + i))
		{
			if (i >= len)
				return (NULL);
			if (*(needle + i) != *(haystack + i))
				break ;
			i++;
		}
		if (!*(needle + i))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
