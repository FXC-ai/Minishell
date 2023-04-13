/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:00:40 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/13 17:31:33 by vgiordan         ###   ########.fr       */
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

    if (result[1] == NULL)
	{
		global_sig.pid = fork();
		if (global_sig.pid == 0)
		{
			process_redirection(result[0], env);
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