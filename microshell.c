#include "microshell.h"


/*
	미니쉘 구현 계획
	1. 토큰 분리 규칙에 따라서 나누기
	
*/


/*
	S : 개행, 스페이스
	A : 일반 문자
	P : 파이프
	Q : 더블쿼트
	q : 싱글쿼트
	r : 리다이렉트 >
	D : 달러표시
	l : 리터럴
	s : 문자열

	a : >> appending
	i : < input
	h : << here doc
*/

int is_del(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
			return 1;
	}
	return 0;
}

int is_space(char a)
{
	if (a == 32 || (a >= 9 && a <= 13))
		return 1;
	return 0;
}

int is_alpha(char a)
{
	if (a >= 'a' && a <= 'z')
		return 1;
	else if (a >= 'A' && a <= 'A')
		return 1;
	return 0;
}

int is_dquotes(char a)
{
	if (a == '"')
		return 1;
	return 0;
}

int is_squotes(char a)
{
	if (a == '\'')
		return 1;
	return 0;
}

int is_redirect(char a)
{
	if (a == '<')
		return 1;
	return 0;
}

int is_input(char a)
{
	if (a == '>')
		return 1;
	return 0;
}

int is_pipe(char a)
{
	if (a == '|')
		return 1;
	return 0;
}

int is_env(char a)
{
	if (a == '$')
		return 1;
	return 0;
}


int tokenizing(char *line, t_comm **cmd)
{
	char *buf = (char *)malloc(sizeof(char) * strlen(line) + 1);
	bzero(buf, strlen(line) + 1);
	int i = 0;

	while (line[i])
	{
		if (is_space(line[i]))
			buf[i] = 'S';
		else if (is_alpha(line[i]))
			buf[i] = 'A';
		else if (is_dquotes(line[i]))
			buf[i] = 'Q';
		else if (is_squotes(line[i]))
			buf[i] = 'q';
		else if (is_pipe(line[i]))
			buf[i] = 'p';
		else if (is_redirect(line[i]))
			buf[i] = 'r';
		else if(line[i] == '$')
			buf[i] = 'D';
		else if (line[i] == '\\')
			buf[i] = 'l';
		else if (is_input(line[i]))
			buf[i] = 'i';
		else
			buf[i] = 'A';
		i++;
	}
	printf("%s\n", buf);
	split_line(line, cmd);
	return 1;
}

void read_input(t_comm **cmd)
{
	char *read = readline("minishell$ ");
	printf("%s\n", read);
	tokenizing(read, cmd);
	add_history(read);
	free(read);
}

void free_list(t_comm *cmd)
{
    t_comm *temp;

    while (cmd != NULL) {
        temp = cmd;      // 현재 노드를 임시 변수에 저장
        cmd = cmd->next; // 다음 노드로 이동

        free(temp->token); // 노드의 token 메모리 해제
        free(temp);        // 노드 자체의 메모리 해제
    }
}


int main(int argc, char **argv)
{
	t_comm *cmd;

	while(1)
	{
		read_input(&cmd);
		free_list(cmd);
		cmd = malloc(sizeof(t_comm));
		cmd = NULL;
	}

}