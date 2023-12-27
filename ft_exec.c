/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:27:56 by seokjyan          #+#    #+#             */
/*   Updated: 2023/12/27 20:57:58 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// libft 대체 함수 strcmp


int ft_redirection_out(int fd, char **args, int i, int flag)
{
    if (flag == trunc)
    {
        if ((fd = open(args[i + 1], O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1)
        {
            perror("open");
            return;
        }
    }
    else
    {
        if ((fd = open(args[i + 1], O_WRONLY|O_CREAT|O_APPEND, 0644)) == -1)
        {
            perror("open");
            return;
        }
    }
    dup2(fd, 1);
    close(fd);
    args[i] = 0;
}


int is_redirect(char **args)
{
    int i;
    int fd;

    i = 0;
    while(args[i])
    {
        if ((strcmp(args[i], "1>") == 0) || strcmp(args[i], ">") == 0)
            ft_redirection_out(fd, args, i, trunc);
        if (strcmp(args[i], ">>") == 0)
            ft_redirection_out(fd, args, i, append);
        if ((strcmp(args[i], "0<") == 0) || (strcmp(args[i], "<") == 0))
            ft_redirection_in();
        if (strcmp(args[i], ">>") == 0)
            ft_redirection_in();
        if (strcmp(args[i], "2>") == 0)
            ft_redirection_err();
    }
    return (0);
}

int is_child(int *fd, char *command, char **args)
{
    close(fd[0]);
    dup2(fd[1], 1);
    if (execve(command, args, NULL) == -1)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

int is_parent(int *fd, pid_t pid, char **args)
{
    close(fd[1]);
	dup2(fd[0], 0);
    if (waitpid(pid, NULL, 0) == -1)
    {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
}

int is_pipe(char **arg) 
{
	int i;

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

void ft_exec(const char *command, char **args) {
    pid_t   pid;
    int     fd[2];
    int     i;

    pid = fork();
    i = 0;
    if (i = is_pipe(args))
        pipe(fd);
    // if (is_redirect())
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
        is_child(fd, command, args);
    else
        is_parent(fd, pid, args);
}
