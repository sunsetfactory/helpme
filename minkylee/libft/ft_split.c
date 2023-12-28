/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 21:55:02 by minkylee          #+#    #+#             */
/*   Updated: 2023/04/07 11:03:00 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *str, char c)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (*str != c)
		{
			count++;
			while (*str && *str != c)
				str++;
		}
		else
			str++;
	}
	return (count);
}

static size_t	get_word(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static char	**put_word(char **words, char const *s, char c, size_t row)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = get_word(s, c);
	while (i < row)
	{
		while (*s == c)
			s++;
		len = get_word(s, c);
		words[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!words[i])
		{
			while (i--)
				free(words[i]);
			free(words);
			return (NULL);
		}
		ft_memcpy(words[i], s, len);
		words[i][len] = '\0';
		s += len;
		i++;
	}
	words[i] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	row;

	if (!s)
		return (NULL);
	row = count_words(s, c);
	words = (char **)malloc(sizeof(char *) * (row + 1));
	if (!words)
		return (NULL);
	words = put_word(words, s, c, row);
	return (words);
}
