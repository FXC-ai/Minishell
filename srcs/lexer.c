/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:00:40 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/15 17:43:06 by fcoindre         ###   ########.fr       */
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
	char *tmp;
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
	//printf("nbr chev %d\n", nbr_chev);
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
			tmp = ft_substr(tab_cmds, i, lenght);
			i += lenght - 2;
			result[j++] = tmp;
			//printf("Result[%d] = [%s]\n", j, tmp);
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
	char *tmp;
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
			tmp = ft_substr(tab_cmds, i, length);
			result[j] = tmp;
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
		current_struct->cmd_args = ft_split_lexer_no_quote(tmp[0]);
		free(tmp);
		current_struct->redirections = separate_redirections(tab_cmds[i]);
		//print_tab("redirections", current_struct->redirections);
		//print_tab(" command ",current_struct->cmd_args);
		list_struct[i] = current_struct;
		i++;
	}
	list_struct[i] = NULL;
	return (list_struct);
}

int lexer(char *str, char *env[])
{
	char	**result;
	char	c = '|';
	int     i;
	int		*in_out_fd;
	int		status;

	int		r;

	in_out_fd = malloc(2 * sizeof(int));

	//int		nbr_cmds;
	//int		status;
	//int		r;
	//char **parsed_args;
	t_parsed_args **cmd_red_lst;

    i = 0;

	result = ft_split_lexer(str, c);
	

	if (result == NULL)
		return 0;
    while (result[i])
    {   
        cut_end_space(&(result[i]));
        i++;
    }


	//normalize_with_space(result);

	//add_space_chevron(result, env);

	parse_dollar(result, env);

	//printf("result = %s");

	//print_tab(result);

	cmd_red_lst = init_parsed_args(result);

	r = is_builtins(cmd_red_lst[0]->cmd_args[0]);
	//printf("r = %d\n", r);






	if (cmd_red_lst[1] == NULL)
	{
		in_out_fd[0] = STDIN_FILENO;
		in_out_fd[1] = STDOUT_FILENO;

		if (process_redirection(cmd_red_lst[0]->redirections, &in_out_fd, env) == -1)
		{
			errno = global_sig.ms_errno;
			return -1;
		}

		if (r == BUILTIN_CD || r == BUILTIN_EXPORT || r == BUILTIN_UNSET || r == BUILTIN_EXIT)
		{
			execute_command(cmd_red_lst[0]->cmd_args, in_out_fd[0], in_out_fd[1], env);
			if (in_out_fd[0] != STDIN_FILENO)
			{
				close(in_out_fd[0]);
			}
			if (in_out_fd[1] != STDOUT_FILENO)
			{
				close(in_out_fd[1]);
			}
		}
		else
		{
			global_sig.pid = fork();
			if (global_sig.pid == 0)
			{
				execute_command(cmd_red_lst[0]->cmd_args, in_out_fd[0], in_out_fd[1], env);
				if (in_out_fd[0] != STDIN_FILENO)
				{
					close(in_out_fd[0]);
				}
				if (in_out_fd[1] != STDOUT_FILENO)
				{
					close(in_out_fd[1]);
				}
				exit(SUCCESS);
			}
			else
			{
				waitpid(global_sig.pid, &status, 0);
				if (WIFEXITED(status))
				{
					global_sig.ms_errno = WEXITSTATUS(status);
				}
			}
		//printf("infd = %d et outfd = %d\n", in_out_fd[0], in_out_fd[1]);+
		}
		
	}
	else
	{
		i = 0;
		while (cmd_red_lst[i] != NULL)
		{
			process_redirection(cmd_red_lst[i]->redirections, &in_out_fd, env);
			//printf("infd = %d et outfd = %d\n", in_out_fd[0], in_out_fd[1]);
			i++;
		}
	}
	





	/*
	parsed_args = ft_split_lexer_no_quote(result[0], ' ');
	
	r = is_builtins(parsed_args[0]);
	if (r != 0 && result[1] == NULL) // Certain builtin doivent etre executer dans le parent et si il y a des pipes ils ne sont pas exec
	{
		if (r == BUILTIN_UNSET || r == BUILTIN_CD || r == BUILTIN_EXIT || r == BUILTIN_EXPORT)
		{
			execute_command(parsed_args, 0, 1, env);
			free(parsed_args);
			free(result);
			return (0);
		}
	}


    if (result[1] == NULL)
	{
		global_sig.pid = fork();
		if (global_sig.pid == 0)
		{
			process_redirection(result[0], env);
			exit(0);
		}
		else
		{
			waitpid(global_sig.pid, &status, 0);
			//ft_putstr_fd("waitpid\n", 2);
			if (WIFEXITED(status))
			{
				global_sig.ms_errno = WEXITSTATUS(status);

			}
		}
		return (0);
	}
	else
	{
		nbr_cmds = size_tab(result);
		ms_pipe2(result, nbr_cmds, env);
	}
	*/
	return (1);
}