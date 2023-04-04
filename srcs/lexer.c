/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:39:34 by fcoindre          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/04 14:16:32 by fcoindre         ###   ########.fr       */
=======
/*   Updated: 2023/04/04 12:18:06 by vgiordan         ###   ########.fr       */
>>>>>>> c56a67f1e4c0da7e3f00fbf811614c6eaa29e351
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
            if ((*p == '<' && *(p + 1) != '<') || (*p == '>' && *(p + 1) != '>'))
            {
                if (prev != NULL && !is_space(*prev) && *prev != '\'' && *prev != '\"' && *prev != '<') {
                ft_memmove(p+1, p, ft_strlen(p)+1);
                *p = ' ';
                prev = p;
                }
                if (*(p+1) != '\0' && !is_space(*(p+1)) && *(p+1) != '\'' && *(p+1) != '\"' && *(p+1) != '<' && *(p + 1) != '>') {
                    ft_memmove(p+2, p+1, ft_strlen(p+1)+1);
                    *(p+1) = ' ';
                }
            }
            p++;

            
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

char *find_env_variable (char *var_name, char *env[])
{
	int i = 0;

	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0 && env[i][ft_strlen(var_name)] == '=')
		{
            return &env[i][ft_strlen(var_name) + 1];
		}
		i++;
	}
    return NULL;

}


void parse_dollar(char **tab_cmds, char *env[])
{
    int i;
    int j;
    char *trimmed_command;
    char *env_variable;
    char *key;
    char *tmp;
    char *str1;
    char *str2;

    i = 0;
    while (tab_cmds[i] != NULL)
    {
        trimmed_command = ft_strchr(tab_cmds[i], '$');
        while (trimmed_command != NULL)
        {
            j = 0;
            while (is_space(trimmed_command[j]) != 1 && trimmed_command[j] != '\0')
                j++;

            key = ft_strndup(trimmed_command+1, j-1);



            env_variable = find_env_variable(key, env);
            if (env_variable != NULL)
            {
                tmp = ft_strndup(tab_cmds[i], ft_strlen(tab_cmds[i]) - ft_strlen(trimmed_command));
                str1 = ft_strjoin(tmp, env_variable);
                str2 = ft_strndup(trimmed_command + j, ft_strlen(trimmed_command + j));
                free(tab_cmds[i]);
                tab_cmds[i] = NULL;
                tab_cmds[i] = ft_strjoin(str1, str2);
                free(key);
                free(tmp);
                free(str1);
                free(str2);
                trimmed_command = ft_strchr(tab_cmds[i], '$');
            }
            else
            {   
                env_variable = "";
                tmp = ft_strndup(tab_cmds[i], ft_strlen(tab_cmds[i]) - ft_strlen(trimmed_command));
                str1 = ft_strjoin(tmp, env_variable);
                str2 = ft_strndup(trimmed_command + j, ft_strlen(trimmed_command + j));
                free(tab_cmds[i]);
                tab_cmds[i] = NULL;
                tab_cmds[i] = ft_strjoin(str1, str2);
                free(key);
                free(tmp);
                free(str1);
                free(str2);
                trimmed_command = ft_strchr(tab_cmds[i], '$');
            }
        }
        i++;
    }
}

char **lexer(char *str, char *env[])
{
	char	**result;
	char	c = '|';
	

	result = ft_split_lexer(str, c);
	if (result == NULL)
		return (0);


	normalize_with_space(result);
	
    //print_tab(result);


	parse_dollar(result, env);


	if (result[1] == NULL)
	{
		process_redirection(result[0], env, 1);
		return (0);
	}

	ms_pipe2(result,env);
	
	return (result);
}