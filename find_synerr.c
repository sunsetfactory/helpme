/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_synerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:46:49 by minkylee          #+#    #+#             */
/*   Updated: 2023/12/28 19:00:17 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int found_squote_err(char *buf)
{
	int i;
	int quote_flag;

	i = 0;
	quote_flag = 0;
	while (buf[i])
	{
		if (!quote_flag && buf[i] == 'q')
			quote_flag = 1;
		else if (quote_flag && buf[i] == 'q')
			quote_flag = 0;
		i++;
	}
	if (quote_flag)
	{
		printf("minishell: syntax error near unexpected token '\n");
		return 0;
	}
	return 1;
}

int found_dquote_err(char *buf)
{
	int i;
	int quote_flag;

	i = 0;
	quote_flag = 0;
	while (buf[i])
	{
		if (!quote_flag && buf[i] == 'Q')
			quote_flag = 1;
		else if (quote_flag && buf[i] == 'Q')
			quote_flag = 0;
		i++;
	}
	if (quote_flag)
	{
		printf("minishell: syntax error near unexpected token \"\n");
		return 0;
	}
	return 1;
}

int pipe_at_the_end(char *buf)
{
	int i;

	i = ft_strlen(buf) - 1;
	while (buf[i] == 'S')
		i--;
	if (buf[i] == 'p')
	{
		if (i == 0 || buf[i - 1] != 'p')
			printf("minishell: syntax error near unexpected token `|'\n");
		else if (buf[i - 1] == 'p')
			printf("minishell: syntax error near unexpected token `||'\n");
		return 0;
	}
	return 1;
}

int only_redirec(char *buf)
{
	int i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] != 'S' && buf[i] != 'r')
			return 1;
		i++;
	}
	printf("minishell: syntax error near unexpected token `newline'\n");
	return 0;
}

int find_syntax_err(char *buf)
{
	if (!found_dquote_err(buf) || !found_squote_err(buf) || !pipe_at_the_end(buf) || !only_redirec(buf))
		return 0;
	return 1;
}
