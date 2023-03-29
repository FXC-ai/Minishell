/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:32:28 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/29 13:58:12 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

void normalize_with_space(char **str)
{
    char *p = *str;
    char *prev = NULL;
    char quote = '\0';

    while (*p != '\0')
	{
        if (quote != '\0' && *p == quote)
		{
            quote = '\0';
        }
		else if (quote == '\0' && (*p == '\'' || *p == '\"'))
		{
            quote = *p;
        }
		else if (quote == '\0' && (*p == '<' || *p == '>'))
		{
            if (prev != NULL && !is_space(*prev) && *prev != '\'' && *prev != '\"' && *prev != '<') {
                memmove(p+1, p, strlen(p)+1);
                *p = ' ';
                prev = p;
            }
            if (*(p+1) != '\0' && !is_space(*(p+1)) && *(p+1) != '\'' && *(p+1) != '\"' && *(p+1) != '<') {
                memmove(p+2, p+1, strlen(p+1)+1);
                *(p+1) = ' ';
            }
        }
        prev = p;
        p++;
    }
}

void	my_error()
{
	exit(EXIT_FAILURE);
}

char **lexer(char *str, char *env[])
{
	char	**result;
	int		i;
	char	c = '|';
	i = 0;
	result = ft_split_lexer(str, c);
	normalize_with_space(result);
	if (result[1] == NULL)
	{
		process_redirection(result[0], env, 1);
		return (0);
	}
	/*while (result[i])
	{
		//printf("str %d = [%s]\n", i, result[i]);
		i++;
	}*/
	ms_pipe2(result,env);
	return (result);
}