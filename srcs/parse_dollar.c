/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:01:12 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/19 18:47:21 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char *find_env_variable (char *var_name)
{
	int	i;

	i = 0;
	while (global_sig.env[i] != NULL)
	{
		if (ft_strncmp(global_sig.env[i], var_name, ft_strlen(var_name)) == 0 && global_sig.env[i][ft_strlen(var_name)] == '=')
		{
            return &global_sig.env[i][ft_strlen(var_name) + 1];
		}
		i++;
	}
	return (NULL);
}

int	check_simple_quote(char *cmd, char *trimmed_command)
{
	int	size_cmd;
	int	size_trimmed_cmd;
	int	size_back;
	int	result;

	result = 2;
	size_cmd = ft_strlen(cmd);
	size_trimmed_cmd = ft_strlen(trimmed_command);
	size_back = size_cmd - size_trimmed_cmd;
	while (size_back > 0)
	{
		if (cmd[size_back] == '\'')
		{
			result--;
			break ;
		}
		if (cmd[size_back] == '\"')
			break ;
		size_back--;
	}
	while (*trimmed_command != '\0')
	{
		if (*trimmed_command == '\'')
		{
			result--;
			break ;
		}
		if (cmd[size_back] == '\"')
			break ;
		trimmed_command++;
	}
	return (result);
}

int	check_simple_quote2(char *cmd, char *trimmed_command)
{
	int		i;
	int		in_quote;
	char	quote;

	quote = '\0';
	in_quote = 0;
	i = 0;
	while (&cmd[i] != trimmed_command)
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			if (in_quote == 0)
			{
				quote = cmd[i];
				in_quote = 1;
			}
			else if (cmd[i] == quote)
			{
				quote = '\0';
				in_quote = 0;
			}
		}
		i++;
	}
	return (in_quote && quote == '\'');
}

void parse_dollar(char **tab_cmds)
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

            //check_simple_quote2(tab_cmds[i], trimmed_command);
            if (check_simple_quote2(tab_cmds[i], trimmed_command) == 0)
            {
                key = ft_strndup(trimmed_command+1, j-1);
                env_variable = find_env_variable(key);
                if (env_variable != NULL)
                {
                    tmp = ft_strndup(tab_cmds[i], ft_strlen(tab_cmds[i]) - ft_strlen(trimmed_command));
                    str1 = ft_strjoin(tmp, env_variable);
                    str2 = ft_strndup(trimmed_command + j, ft_strlen(trimmed_command + j));

                    //printf("tmp = [%s] | str1 = [%s] | str2 = [%s]\n", tmp, str1, str2);

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
                        env_variable = ft_strdup("");

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
                    free(env_variable);
                    trimmed_command = ft_strchr(tab_cmds[i], '$');
                }
            }
            else
            {
                trimmed_command = ft_strchr(trimmed_command +1, '$');
            }
        }
        //printf("result = [%s]\n", tab_cmds[i]);
        i++;
    }
}