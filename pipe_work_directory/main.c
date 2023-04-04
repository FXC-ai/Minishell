#include "../includes/header.h"

char *find_env_variable (char *var_name, char *env[]);

int	size_tab(char **tab)
{
	int	count;

	count = 0;
	while (tab[count] != NULL)
		count++;
	return (count);
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



static char *replace_dollar (char *tab_cmd, char *env_variable, char *trimmed_command, int j)
{
    char *key;
    char *tmp;
    char *str1;
    char *str2;
    char *str;

    //printf("Dans replace_dollar = %p\n", tab_cmd);

    tmp = ft_strndup(tab_cmd, ft_strlen(tab_cmd) - ft_strlen(trimmed_command));
    str1 = ft_strjoin(tmp, env_variable);
    str2 = ft_strndup(trimmed_command + j, ft_strlen(trimmed_command + j));

    str = ft_strjoin(str1, str2);
    free(key);
    key = NULL;
    free(tmp);
    tmp = NULL;
    free(str1);
    str1 = NULL;
    free(str2);
    str2 = NULL;
    
    return str;
    //printf("Dans replace_dollar apres = %p\n", tab_cmd);

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
                trimmed_command = ft_strchr(trimmed_command+1, '$');
                free(key);
            }
        }
        i++;
    }
}

void	print_tab(char **tab)
{
	int i;

	i = 0;
	printf("--------------TAB------------\n");
	while (tab[i])
	{
		printf("%s\n", tab[i++]);
	}
	printf("-----------------------------\n");
}

void	ft_free_tabs(char **tab, int h)
{
	int	i;

	i = 0;
	while (i <= h)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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


int main (int argc, char *argv[], char *env[])
{

    char **testeur = malloc(sizeof(char *) * 2);


    testeur[0] = ft_strdup("echo $ ");
    testeur[1] = NULL;


    print_tab(testeur);
    parse_dollar(testeur, env);
    print_tab(testeur);


    //ft_free_tabs(testeur, size_tab(testeur));

    return 0;
}