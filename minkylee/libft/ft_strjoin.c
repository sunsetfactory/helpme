/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:38:50 by minkylee          #+#    #+#             */
/*   Updated: 2023/12/28 15:39:50 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(char const *s1, char const *s2) 
{
    if (!s1 || !s2) return NULL;
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
    if (!str) return NULL;
    ft_strlcpy(str, s1, len1 + 1);
    ft_strlcat(str, s2, len1 + len2 + 1);
    return str;
}
