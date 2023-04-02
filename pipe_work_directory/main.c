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




char **parse_dollar_dep(char **result_split, char *env[])
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





void parse_dollar(char **tab_cmds, char *env[])
{

    int i;
    int j;
    char *trimmed_command;
    char *env_variable;
    char *key;
    char *tmp2;
    char *str1;
    char *str2;
    int size_str1;


    char *debug_var;

    i = 0;
    while (tab_cmds[i] != NULL)
    {
    
        trimmed_command = ft_strchr(tab_cmds[i], '$');
        while (trimmed_command != NULL)
        {
            
            j =0;
            while (is_space(trimmed_command[j]) != 1 && trimmed_command[j] != '\0')
            {
                j++;
            }
            key = ft_strndup(trimmed_command+1, j-1);
                
            env_variable = find_env_variable(key, env);
            if (env_variable != NULL)
            {
                size_str1 = ft_strlen(tab_cmds[i]) - ft_strlen(trimmed_command);
                str1 = ft_strndup(tab_cmds[i], size_str1);
                tmp2 = ft_strjoin(str1, env_variable);

                //Le calcule de la taille de str2 est pas juste
                str2 = ft_strndup(trimmed_command + j, ft_strlen(trimmed_command + j));

                free(tab_cmds[i]);
                tab_cmds[i] = NULL;
                tab_cmds[i] = ft_strjoin(tmp2, str2);
                debug_var = tab_cmds[i];

                trimmed_command = ft_strchr(tab_cmds[i], '$');
                free(key);
                free(tmp2);
                free(str1);
                free(str2);

            }
            else
            {   
                trimmed_command = ft_strchr(trimmed_command+1, '$');

            }
        }
        printf("tab_cmds[%d] : %s\n",i, tab_cmds[i]);
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

    char **testeur = malloc(sizeof(char *) * 5);


    testeur[0] = ft_strdup("echo $USER $USER $er $USER");
    testeur[1] = ft_strdup("echo $HOME $ LOGNAME $er $LOGNAME");
    testeur[2] = ft_strdup("echo $USR $ USER $er $USER     ");
    testeur[3] = ft_strdup("echo         $USER $SHELL SHELL $  USER $USER $er $USER");
    testeur[4] = NULL;


    parse_dollar(testeur, env);
    //print_tab(testeur);

    //printf("%s\n",find_env_variable("PATH", env));





    ft_free_tabs(testeur, size_tab(testeur));

    return 0;
}