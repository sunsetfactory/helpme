/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:40:24 by seokjyan          #+#    #+#             */
/*   Updated: 2023/12/28 17:59:41 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_pipe(char *com)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	if (pipe(fd) == -1)
		exit(1);
	pid1 = fork();
	if (pid1 < 0)
	{
		close(fd[0]);
		close(fd[1]);
		perror("error");
		exit(1);
	}
	if (pid1 == 0)
		execve(com, NULL, NULL);
	else
		
	return (fd);
}
