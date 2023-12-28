/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:49:50 by seokjyan          #+#    #+#             */
/*   Updated: 2023/12/28 16:04:41 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_document(char *args, int i)
{
	char	*delimiter;
	char	*input;
	size_t	input_size;
	size_t	arg_len;

	delimiter = args[i + 1];
	i += 2;
	while (args[i] && strcmp(args[i], delimiter) != 0)
	{
		arg_len = strlen(args[i]);
		input = malloc(sizeof(char *) * (input_size + arg_len + 2));
		if (!input)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strcat(input, args[i]);
		strcat(input, " ");
		input_size += arg_len + 1;
		i++;
	}
}

int	ft_redirection_in(int fd, char **args, int i)
{
	if ((fd = open(args[i + 1], O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	dup2(fd, 1);
	close(fd);
	args[i] = 0;
	return (EXIT_SUCCESS);
}

int	ft_redirection_out(int fd, char **args, int i, int flag)
{
	if (flag == trunc)
	{
		if ((fd = open(args[i + 1], O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1)
		{
			perror("open");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		if ((fd = open(args[i + 1], O_WRONLY|O_CREAT|O_APPEND, 0644)) == -1)
		{
			perror("open");
			return (EXIT_FAILURE);
		}
	}
	dup2(fd, 1);
	close(fd);
	args[i] = 0;
	return (EXIT_SUCCESS);
}

int	is_redirect(char **args)
{
	int	i;
	int	fd;

	i = 0;
	while (args[i])
	{
		if ((strcmp(args[i], "1>") == 0) || strcmp(args[i], ">") == 0)
			ft_redirection_out(fd, args, i, trunc);
		if (strcmp(args[i], ">>") == 0)
			ft_redirection_out(fd, args, i, append);
		if ((strcmp(args[i], "0<") == 0) || (strcmp(args[i], "<") == 0))
			ft_redirection_in(fd, args, i);
		if (strcmp(args[i], "<<") == 0)
			ft_here_document(args, i);
		if (strcmp(args[i], "2>") == 0)
			ft_redirection_err();
	}
	return (0);
}


// if (end_char == F_QUOTED)
// 	param_expansion(str);

// 1. end_char가 따옴표로 묶여있는 경우
// 	- 받아온 환경변수에 대한 확장을 일으킨다
// 2. end_char가 따옴표로 묶여있지 않은 경우
// 	- 받아온 환경변수를 확장하지 않는다.
