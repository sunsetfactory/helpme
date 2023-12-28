/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:38:50 by minkylee          #+#    #+#             */
/*   Updated: 2023/04/07 11:17:02 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		strlen;
	char	*str;

	strlen = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * strlen + 1);
	if (!str)
		return (NULL);
	str[strlen--] = '\0';
	while (strlen >= 0)
	{
		str[strlen] = s[strlen];
		strlen--;
	}
	return (str);
}
