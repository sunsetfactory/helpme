/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkylee <minkylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 20:33:37 by minkylee          #+#    #+#             */
/*   Updated: 2023/12/27 22:04:16 by minkylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void print(t_comm *cmd)
{
	while (cmd)
	{
		printf("token : %s\n", cmd->token);
		cmd = cmd->next;
	}
}

/* start ~ end 까지의 문자열 반환하는 함수 */
char *mk_strdup(int start, int end, char *line)
{
    char *new_line;
    int i;

    new_line = (char *)malloc(sizeof(char) * (end - start + 2));
    if (new_line == NULL)
        return NULL; // 할당 실패 시 NULL 반환
    i = 0;
    while (start <= end)
    {
        if (line[start] == '\0') 
			break;
        new_line[i++] = line[start++];
    }
    new_line[i] = '\0';
    return new_line;
}

char *find_delimited(char *token, t_comm **cmd)
{
    int i = 0;
    int start = i;
    char *new_token;
	int del_flag = 0;

    while (token[i])
    {
        // 리다이렉션과 파이프 기호 처리
        if (token[i] == '<' || token[i] == '>' || token[i] == '|')
        {
            // 현재까지의 일반 문자열 출력
            if (i > start)
            {
                new_token = mk_strdup(start, i - 1, token);
                init_list(cmd, new_token, STR);
                free(new_token);
            }

            // 리다이렉션과 파이프 기호 출력
            if ((token[i] == '<' || token[i] == '>') && token[i + 1] == token[i])
            {
                new_token = mk_strdup(i, i + 1, token);
				init_list(cmd, new_token, RED);
                i += 2;
            }
            else
            {
                new_token = mk_strdup(i, i, token);
				init_list(cmd, new_token, RED);
                i++;
            }
            free(new_token);
            start = i;
        }
        else
            i++;
    }

    // 마지막 일반 문자열이 있으면 출력
    if (i > start)
        new_token = mk_strdup(start, i - 1, token);
	else
		new_token = ft_strdup("");
	return new_token;
}

char *process_dquo(char *line, int start)
{
    int end = start + 1;
    char *token;
    while (line[end])
    {
        if (is_dquotes(line[end]))
		{
            token = mk_strdup(start + 1, end - 1, line);
			break;
		}
        end++;
    }
    return token;
}

char *process_squo(char *line, int start)
{
    int end = start + 1;
    char *token;
    while (line[end])
    {
        if (line[end] == '\'')
		{
            token = mk_strdup(start + 1, end - 1, line);
			return token;
		}
        end++;
    }
    return NULL;
}

void init_list(t_comm **cmd, char *token, int type)
{
    t_comm *push = (t_comm *)malloc(sizeof(t_comm));
    if (!push) return;  // 메모리 할당 확인

    // 새 노드 초기화
    push->token = strdup(token);  // 토큰 복사하여 저장
    push->length = ft_strlen(token);
    push->type = type;
    push->next = NULL;

    // 리스트의 끝을 찾고 새 노드 추가
    if (*cmd == NULL) {
        *cmd = push;
    } else {
        t_comm *temp = *cmd;
        while (temp->next)
            temp = temp->next;
        temp->next = push;
    }
}

/* 문자를 나눠용 */
void split_line(char *line, t_comm **cmd)
{
	int i = 0;
	int token_index = 0;
	char *quote_temp;
	char *temp = (char *)malloc(sizeof(char) * strlen(line) + 1);
	char *token;
	t_comm **head = cmd;
	bzero(temp, strlen(line) + 1);

	while (line[i])
	{
		if (is_space(line[i]) || line[i + 1] == '\0')
		{
			if (!is_space(line[i]) && line[i + 1] == '\0') 
                temp[token_index++] = line[i];  // 마지막 글자 추가
			token = mk_strdup(0, token_index, temp);
			bzero(temp, strlen(line) + 1);
			token_index = 0;
			init_list(cmd, token, STR);
			free(token);
			i++;
			continue;
		}
		else if (is_squotes(line[i]))
		{
			quote_temp = ft_strjoin(find_delimited(temp, cmd), process_squo(line, i));
			bzero(temp, ft_strlen(quote_temp) + 1);
			ft_strlcat(temp, quote_temp, ft_strlen(quote_temp) + 1);
			i += ft_strlen(quote_temp);
			token_index += ft_strlen(quote_temp);
			free(quote_temp);
		}
		else if (is_dquotes(line[i]))
		{
			quote_temp = ft_strjoin(find_delimited(temp, cmd), process_dquo(line, i));
			bzero(temp, ft_strlen(quote_temp) + 1);
			ft_strlcat(temp, quote_temp, ft_strlen(quote_temp) + 1);
			i += ft_strlen(quote_temp);
			token_index += ft_strlen(quote_temp);
			free(quote_temp);
		}
		else
			temp[token_index] = line[i];
		token_index++;
		i++;
	}
	print(*head);
}

/* 환경변수 값을 대치합니다.*/
void process_env_var(char **token)
{
    char *var_name;
	char *var_value;
	char *new_token;
    int start = 0;

    char *dollar_pos = strchr(*token, '$');
    if (dollar_pos == NULL) 
		return; // '$' 없으면 종료

    var_name = dollar_pos + 1;
    var_value = getenv(var_name); // 환경변수 값 찾기

    if (var_value)
	{
        // 환경변수 값으로 대체
        *dollar_pos = '\0'; // '$' 앞부분 잘라내기
        new_token = (char *)malloc(strlen(*token) + strlen(var_value) + strlen(dollar_pos + strlen(var_name) + 1) + 1);
        if (new_token) 
		{
            strcpy(new_token, *token); // '$' 앞부분 복사
            strcat(new_token, var_value); // 환경변수 값 추가
            strcat(new_token, dollar_pos + strlen(var_name) + 1); // 환경변수 이름 이후 부분 추가
            free(*token); // 원래 토큰 메모리 해제
            *token = new_token; // 새 토큰으로 업데이트
        }
    }
}
