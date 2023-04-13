/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:00:40 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/13 14:33:57 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int lexer(char *str, char *env[])
{
	char	**result;
	char	c = '|';
	int     i;
	int		nbr_cmds;

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

	//print_tab(result);

	parse_redirection_right(result);
	

	//(void) nbr_cmds;
	parse_redirection_left(result);
	print_tab(result);
	
	print_tab(result);
    if (result[1] == NULL)
	{
		process_redirection(result[0], env, 1);
		//return (0);
	}
	else
	{
		nbr_cmds = size_tab(result);
		ms_pipe2(result, nbr_cmds, env);
	}
	return (1);
}