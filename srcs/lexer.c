/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:00:40 by vgiordan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/13 15:40:54 by fcoindre         ###   ########.fr       */
=======
/*   Updated: 2023/04/13 15:10:29 by vgiordan         ###   ########.fr       */
>>>>>>> 12b7b475de22138881fb587d0865bfb385e314b0
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
<<<<<<< HEAD
	
	print_tab(result);
	
	parse_dollar(result, env);


	parse_redirection_left(result);
	parse_redirection_right(result);
	

	//(void) nbr_cmds;
	print_tab(result);
=======
	parse_dollar(result, env);

	parse_redirection_right(result);
	parse_redirection_left(result);
>>>>>>> 12b7b475de22138881fb587d0865bfb385e314b0
	
	print_tab(result);
    if (result[1] == NULL)
	{
		process_redirection(result[0], env, 1);
	}
	else
	{
		nbr_cmds = size_tab(result);
		ms_pipe2(result, nbr_cmds, env);
	}
	return (1);
}