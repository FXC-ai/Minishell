/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:39:34 by fcoindre          #+#    #+#             */
/*   Updated: 2023/03/30 18:40:28 by fcoindre         ###   ########.fr       */
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
                ft_memmove(p+1, p, ft_strlen(p)+1);
                *p = ' ';
                prev = p;
            }
            if (*(p+1) != '\0' && !is_space(*(p+1)) && *(p+1) != '\'' && *(p+1) != '\"' && *(p+1) != '<') {
                ft_memmove(p+2, p+1, ft_strlen(p+1)+1);
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


char *ft_strndup(char *str, size_t n)
{
    
    char    	*result;
    size_t     i;

    if (str == NULL)
        return NULL;

    
    if (ft_strlen(str) <= n)
    {
        return ft_strdup(str);
    }
    
    result = malloc(sizeof(char) * (n + 1));
    if (result == NULL)
        return NULL;

    i = 0;
    while(i < n)
    {
        result[i] = str[i];
        i++;
    }
    result[n] = '\0';

    return result;
}




char **parse_dollar(char **result_split, char *env[])
{

	char *trimmed_command;
	int i;
	int j;
	int sizetab;
	char **result;
	char *tmp;

	sizetab = size_tab(result_split);

	result = malloc(sizeof(char *) * sizetab);
	if (result == NULL)
		return (NULL);

	i = 0;
	while(result_split[i] != NULL)
	{
		trimmed_command = ft_strchr(result_split[i], '$');
		if (trimmed_command != NULL)
		{
			j = 0;
			while (is_space(trimmed_command[j]) != 1)
			{
				j++;
			}
			tmp = ft_strndup(trimmed_command+1, j);
			
			printf("result = %s\n", tmp);

			j = 0;
			while (env[i] != NULL)
			{
				if (ft_strncmp(env[i], tmp, ft_strlen(tmp)) == 0 && env[i][ft_strlen(tmp)] == '=')
				{
					while (env[i] != NULL)
					{
						env[i] = env[i + 1];
						i++;
					}
					break;
				}
				i++;
			}
			

			

			
		}
		else
		{
			result[i] = ft_strdup(result_split[i]);

		}
		i++;
	}

	return result;


}

char **lexer(char *str, char *env[])
{
	char	**result;
	char	c = '|';
	

	result = ft_split_lexer(str, c);
	if (result == NULL)
		return (0);


	normalize_with_space(result);
	
	//parse_dollar(result);

	(void) env;


	
	//print_tab(result);



	if (result[1] == NULL)
	{
		process_redirection(result[0], env, 1);
		return (0);
	}

	ms_pipe2(result,env);
	
	return (result);
}