/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:03:16 by seokjyan          #+#    #+#             */
/*   Updated: 2023/12/28 19:03:50 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICROSHELL_H
#define MICROSHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft/libft.h"

typedef struct s_comm
{
	char			*token;
	int				length;
	int				type;
	int				pipes[2];
	struct s_comm	*prev;
	struct s_comm	*next;
} t_comm;

#define STR 0
#define PIP 1
#define RED 2

/* tokenize */
void split_line(char *line, t_comm **cmd);
char *mk_strdup(int start, int end, char *line);
void process_env_var(char **token);
void init_list(t_comm **cmd, char *token, int type);

int is_space(char a);
int is_dquotes(char a);
int is_squotes(char a);
int is_del(char *line);

#endif