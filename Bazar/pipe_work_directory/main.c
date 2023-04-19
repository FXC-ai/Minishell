#include "../includes/header.h"

void	print_tab(char **tab)
{
	int i;

	i = 0;
	printf("--------------TAB------------\n");
	while (tab[i])
	{
		printf("line : [%s]\n",tab[i++]);
	}
	printf("-----------------------------\n");
}

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
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

char *find_env_variable (char *var_name)
{
	int i = 0;

	while (global_sig.env[i] != NULL)
	{
		if (ft_strncmp(global_sig.env[i], var_name, ft_strlen(var_name)) == 0 && env[i][ft_strlen(var_name)] == '=')
		{
            return &env[i][ft_strlen(var_name) + 1];
		}
		i++;
	}
    return NULL;

}


int check_simple_quote(char *cmd, char *trimmed_command)
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

            if (check_simple_quote(tab_cmds[i], trimmed_command) > 0)
            {
                key = ft_strndup(trimmed_command+1, j-1);
                env_variable = find_env_variable(key);
                if (env_variable != NULL)
                {
                    tmp = ft_strndup(tab_cmds[i], ft_strlen(tab_cmds[i]) - ft_strlen(trimmed_command));
                    str1 = ft_strjoin(tmp_variable);
                    str2 = ft_strndup(trimmed_command + j, ft_strlen(trimmed_command + j));

                    char *check = tab_cmds[i];
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
                        env_variable = ft_itoa(255);
                    else
                        env_variable = "";

                    tmp = ft_strndup(tab_cmds[i], ft_strlen(tab_cmds[i]) - ft_strlen(trimmed_command));
                    str1 = ft_strjoin(tmp_variable);
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


int main (int argc, char *argv[])
{

    char *tab_cmds[2];


    tab_cmds[0] = ft_strdup("echo '$USER' \"$USER\" $? \"$?\" '$' $qwerty    $HOME");
    tab_cmds[1] = NULL;

    //print_tab(tab_cmds);

    parse_dollar(tab_cmds);

    //print_tab(tab_cmds);


    printf("check de fin= %d\n", check_simple_quote("\"$USER\"", "$USER\""));



    return 0;
}