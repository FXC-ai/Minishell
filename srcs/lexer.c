/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:00:40 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/14 13:45:44 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"
int lexer(char *str, char *env[])
{
	char	**result;
	char	c = '|';
	int     i;
	int		nbr_cmds;
	int		status;
	int		r;
	char **parsed_args;

    i = 0;

	result = ft_split_lexer(str, c);
	
	
	


	if (result == NULL)
		return 0;
    while (result[i])
    {   
        cut_end_space(&(result[i]));
        i++;
    }


	normalize_with_space(result);

	parse_dollar(result, env);

	parse_redirection_right(result);
	
	parse_redirection_left(result);
	
	//print_tab(result);
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
	return (1);
}