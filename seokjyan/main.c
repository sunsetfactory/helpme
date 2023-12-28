/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seokjyan <seokjyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:52:51 by seokjyan          #+#    #+#             */
/*   Updated: 2023/12/28 18:43:25 by seokjyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// int main(int argc, char** argv)
// {
// 	int		fd;
// 	char	*init = "ok?\n";
// 	fd = open("talk.txt", O_WRONLY|O_CREAT|O_APPEND, 0644);
// 	printf("%zd \n",write(fd, init, strlen(init)));

//     // ls 명령어 실행
//     printf("Executing ls:\n");
//     char *ls_argv[] = { "ls", "-la", NULL };
//     execve("/bin/ls", ls_argv, NULL);

//     printf("Executing ls -la:\n");
//     // char *ls_argv[] = { "ls", "-la", NULL };
//     execve("/bin/ls", ls_argv, NULL);

//     printf("Executing ls -laR:\n");
//     // char *ls_argv[] = { "ls", "-laR", NULL };
//     execve("/bin/ls", ls_argv, NULL);
// 	// ft_exec();
// 	// ft_pipe();
// 	return (0);
// }

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return 1;
    }

    // 입력된 명령어를 토큰화하여 execve 함수에 전달
    char *token = strtok(argv[1], " ");
    char *args[32]; // 적절한 크기의 배열로 가정

    int i = 0;
    while (token != NULL && i < 31) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // execve 함수의 인자 배열은 NULL로 끝나야 함

    // execve 함수를 사용하여 명령어 실행
    execve("/bin/ls", args, NULL);

    // execve 함수가 리턴했다는 것은 오류가 발생했다는 뜻
    // perror("execve");
    return 1;
}
