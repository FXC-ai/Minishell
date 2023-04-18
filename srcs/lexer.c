/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:00:40 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/18 23:12:18 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int is_valid_chevron (char *tab_cmd, char chev_type)
{
    int i;
    int count;
	int in_quote;
	char quote;

    count = 0;
    i = 0;
	in_quote = 0;
	quote = '\0';
    while (tab_cmd[i] != '\0')
    {
		if (tab_cmd[i] == '\'' || tab_cmd[i] == '\"')
		{
			if (in_quote == 0)
			{
				quote = tab_cmd[i];
				in_quote = 1;
			}
			else if (tab_cmd[i] == quote)
			{
				quote = '\0';
				in_quote = 0;
			}
		}
        if (tab_cmd[i] == chev_type && in_quote == 0)
        {
            if (tab_cmd[i + 1] == chev_type)
                i++;
            i++;
            while (is_space(tab_cmd[i]) == 1)
                i++;
            if (is_chevron(tab_cmd[i]) == 1)
                return -1;
            count++;
        }
        i++;
    }
    return count;
}

static int find_lenght(char *cmd, char chev_type)
{
    int i;
	int lenght;

    i = 0;
    lenght = 0;

    while (cmd[i])
    {
        if (cmd[i] == chev_type)
        {

            if (cmd[i+1] == chev_type)
            {
                i++;
            }
            i++;
            while (is_space(cmd[i]) == 1)
            {
                i++;
            }
            while (cmd[i] && cmd[i] != ' ' && !is_chevron(cmd[i]))
            {
                i++;
            }
            lenght = i;
            break;
        }
        i++;
    }
	return lenght;
}

static int find_lenght_command(char *cmd)
{
	int	i;
	int in_quote;
	char quote;
	int length;

	in_quote = 0;
	quote = '\0';
	i = 0;
	length = 0;
	while (cmd[i])
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
			//printf("quote = %c in_quote = %d\n", quote, in_quote);
		}
		if (cmd[i] && in_quote == 0 && is_chevron(cmd[i]))
		{
			
			return (length);
		}
		length++;
		i++;
	}
	return (length);
}

char **separate_redirections (char *tab_cmds)
{
	int i;
	int j;
	int lenght;
	int in_quote;
	char quote;
	char **result;
	int	nbr_chev;

	quote = '\0';
	in_quote = 0;
	i = 0;
	j = 0;
	nbr_chev = is_valid_chevron(tab_cmds, '>');
	nbr_chev += is_valid_chevron(tab_cmds, '<');
	result = malloc(sizeof(char *) * (nbr_chev + 1));
	if (result == NULL)
	{
		return (NULL);
	}
	while (tab_cmds[i])
	{	
		if (tab_cmds[i] == '\'' || tab_cmds[i] == '\"')
		{
			if (in_quote == 0)
			{
				quote = tab_cmds[i];
				in_quote = 1;
			}
			else if (tab_cmds[i] == quote)
			{
				quote = '\0';
				in_quote = 0;
			}
		}
		if (in_quote == 0 && (tab_cmds[i] == '<' || tab_cmds[i] == '>'))
		{
			lenght = find_lenght(tab_cmds+i, tab_cmds[i]);
			result[j++] = ft_substr(tab_cmds, i, lenght);
			i += lenght - 2;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

char **separate_command (char *tab_cmds)
{
	int i;
	int j;
	int length;
	char **result;

	j = 0;
	i = 0;
	while (tab_cmds[i])
	{
		length = find_lenght_command(tab_cmds + i);
		if (length != 0)
			j++;
		i+=length;
		while (is_chevron(tab_cmds[i]))
		{			
			while (tab_cmds[i] && is_chevron(tab_cmds[i]))
				i++;
			while (tab_cmds[i] && (is_space(tab_cmds[i])))
				i++;
			while (tab_cmds[i] && !is_space(tab_cmds[i]) && !is_chevron(tab_cmds[i]))
				i++;
			while (tab_cmds[i] && (is_space(tab_cmds[i])))
				i++;
		}
	}
	result = malloc((j + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);

	i = 0;
	j = 0;
	while (tab_cmds[i])
	{
		
		length = find_lenght_command(tab_cmds + i);
		if (length != 0)
		{
			result[j] = ft_substr(tab_cmds, i, length);
			j++;
		}
		i+=length;
		while (is_chevron(tab_cmds[i]))
		{			
			while (tab_cmds[i] && is_chevron(tab_cmds[i]))
				i++;
			while (tab_cmds[i] && (is_space(tab_cmds[i])))
				i++;
			while (tab_cmds[i] && !is_space(tab_cmds[i]) && !is_chevron(tab_cmds[i]))
				i++;
			while (tab_cmds[i] && (is_space(tab_cmds[i])))
				i++;
		}
	}
	result[j] = NULL;
	//print_tab("separate command", result);
	return (result);
}

t_parsed_args **init_parsed_args (char **tab_cmds)
{
	t_parsed_args **list_struct;
	t_parsed_args *current_struct;
	char **tmp;
	int i;

	list_struct = malloc((size_tab(tab_cmds) + 1) * sizeof(t_parsed_args * ));
	if (list_struct == NULL)
		return (NULL);
	i = 0;
	while (tab_cmds[i])
	{
		current_struct = malloc(sizeof(t_parsed_args));
		if (current_struct == NULL)
			return (NULL);
		tmp = separate_command(tab_cmds[i]);
		current_struct->cmd_args = ft_split_lexer_no_quote(concatenate_strings_with_spaces(tmp));
		freemalloc(tmp, size_tab(tmp));
		current_struct->redirections = separate_redirections(tab_cmds[i]);
		//print_tab("redirections", current_struct->redirections);
		//print_tab(" command ",current_struct->cmd_args);
		list_struct[i] = current_struct;
		i++;
	}
	list_struct[i] = NULL;
	return (list_struct);
}


char	check_redirections (char *str, char type_chev)
{
	char *str_from_chev;

	str_from_chev = ft_strchr(str, type_chev);
	if (str_from_chev != NULL)
	{
		str_from_chev++;
		if (*str_from_chev == type_chev)
			str_from_chev++;
		while (is_space(*str_from_chev) == 1)
			str_from_chev++;
		if (is_chevron(*str_from_chev) == 1 || *str_from_chev == '\0')
		{
			global_sig.ms_errno = 258;
			return *str_from_chev;
		}
	}
	return 1;
}

char *error_redirection_msg (char chr_err)
{
	if (chr_err == '>')
		return ft_strdup("minishell: syntax error near unexpected token `>'\n");
	else if (chr_err == '<')
		return ft_strdup("minishell: syntax error near unexpected token `<'\n");
	return ft_strdup("minishell: syntax error near unexpected token `newline'\n");
}

int check_redirections_process (char **tab_cmds)
{
	int i;
	int result;
	char *error_msg;

	result = 0;
	i = 0;
	while (tab_cmds[i] != NULL)
	{
		if (check_redirections(tab_cmds[i], '>') != 1)
		{
			error_msg = error_redirection_msg(check_redirections(tab_cmds[i], '>'));
			ft_putstr_fd(error_msg, 2);
			free(error_msg);
			return (0);
		}
		else if (check_redirections(tab_cmds[i], '<') == 0)
		{
			error_msg = error_redirection_msg(check_redirections(tab_cmds[i], '<'));
			ft_putstr_fd(error_msg, 2);
			free(error_msg);
			return (0);
		}
		else if (check_redirections(tab_cmds[i], '<') == '\0' || check_redirections(tab_cmds[i], '>') == '\0')
		{
			error_msg = error_redirection_msg('\0');
			ft_putstr_fd(error_msg, 2);
			free(error_msg);
			return (0);
		}
		i++;
	}
	return (1);
}


int lexer(char *str, char *env[])
{
	char	**result;
	char	c = '|';
	int     i;
	int		*in_out_fd;
	t_parsed_args **cmd_red_lst;

	in_out_fd = malloc(2 * sizeof(int));
	if (in_out_fd == NULL)
		return 0;

    i = 0;
	result = ft_split_lexer(str, c);

	//print_tab("ft_split_lexer", result);
	if (check_redirections_process(result) == 0)
	{
		free(in_out_fd);
		freemalloc(result, size_tab(result));
		return (1);
	}

	if (result == NULL)
		return 0;
    while (result[i])
    {   
        cut_end_space(&(result[i]));
        i++;
    }

	parse_dollar(result, env);

	cmd_red_lst = init_parsed_args(result);
	freemalloc(result, size_tab(result));

	
	in_out_fd[0] = STDIN_FILENO;
	in_out_fd[1] = STDOUT_FILENO;

	if (cmd_red_lst[1] == NULL)
	{
		if (process_single_command(cmd_red_lst, in_out_fd, env) == -1)
			return (-1);	
	}
	else
	{
		if (process_multiple_commands(cmd_red_lst, env) == -1)
			return (-1);
	}
	free(in_out_fd);
	free_struct(cmd_red_lst);
	return (1);
}