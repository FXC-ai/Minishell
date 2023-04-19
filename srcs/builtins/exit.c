#include "../../includes/header.h"

int is_numeric (char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

char *error_msg (char *arg)
{
    char *tmp;
    char *result;

    tmp = ft_strjoin("minishell: exit: ", arg);
    result = ft_strjoin(tmp, ": numeric argument required\n");
    free(tmp);
    return (result);
}

void    exit_process(char **parsed_args)
{
    int     nbr_tokens;
    int     error_code;
    char    *err_msg;

    nbr_tokens = size_tab(parsed_args) - 1;
    if (nbr_tokens == 1)
    {
        if (is_numeric(parsed_args[1]) == 1)
        {
            error_code = ft_atoi(parsed_args[1]);
            ft_putstr_fd("exit\n", 2);
            exit(error_code % 255);
        }
        else
        {
            err_msg = error_msg(parsed_args[1]);
            ft_putstr_fd("exit\n", 2);
            ft_putstr_fd(err_msg, 2);
            free(err_msg);
            exit(255);
        }    
    }
    else if (nbr_tokens > 1)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n",2);
        exit (255);
    }
    ft_putstr_fd("exit\n", 2);
    exit(0);
}
