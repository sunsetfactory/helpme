/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:52:31 by seokjyan          #+#    #+#             */
/*   Updated: 2023/12/28 19:06:13 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_child(int *fd, char *bin, char **args)
{
	close(fd[0]);
	dup2(fd[1], 1);
	if (execve(bin, args, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

int	is_parent(int *fd, pid_t pid, char **args)
{
	close(fd[1]);
	dup2(fd[0], 0);
	if (waitpid(pid, NULL, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

int	is_pipe(char **arg) 
{
	int	i;

	for(i = 0; arg[i]; i++)
	{
		if (strcmp(arg[i], "|") == 0)
		{
			arg[i] = NULL;
			return i;
		}
	}
	return (0);
}

void	ft_exec(const char *bin, char **args)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		i;

	pid = fork();
	i = 0;
	if (i = is_pipe(args))
		pipe(pipe_fd);
	// if (is_redirect())
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		is_child(pipe_fd, bin, args);
	else
		is_parent(pipe_fd, pid, args);
}
