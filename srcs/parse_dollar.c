/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:01:12 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/06 11:02:09 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

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


static int check_simple_quote(char *cmd, char *trimmed_command)
{
    int size_cmd;
    int size_trimmed_cmd;
    int size_back;
    int result;

    result = 2;    
    size_cmd = ft_strlen(cmd);
    size_trimmed_cmd = ft_strlen(trimmed_command);
    size_back = size_cmd - size_trimmed_cmd;

    while (size_back > 0)
    {
        if (cmd[size_back] == '\'')
        {
            result--;
            break;
        }
        if (cmd[size_back] == '\"')
        {
            break;
        }
        size_back--;
    }

    while (*trimmed_command != '\0')
    {
        if (*trimmed_command == '\'')
        {
            result--;
            break;
        }
        if (cmd[size_back] == '\"')
        {
            break;
        }
        trimmed_command++;
    }
    return result;
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
        
        while (trimmed_command != NULL && *trimmed_command != '\0')
        {
            j = 0;
            while (is_space(trimmed_command[j]) != 1 
                    && trimmed_command[j] != '\0'
                    && trimmed_command[j] != '\''
                    && trimmed_command[j] != '\"')
                j++;

            if (check_simple_quote(tab_cmds[i], trimmed_command) > 0)
            {
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
                    if (trimmed_command[1] == '?')
                        env_variable = ft_itoa(global_sig.ms_errno);
                    else
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
            else
            {
                trimmed_command = ft_strchr(trimmed_command +1, '$');
            }
        }
        i++;
    }
}