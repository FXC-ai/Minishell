/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 17:36:30 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/15 17:57:41 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int		string_has_right_redirection(char *str)
{
	int	count;

	count = count_chr(str, '>');
	return (count - 1);
}

int		string_has_left_redirection(char *str)
{
	int	count;

	count = count_chr(str, '<');
	return (count - 1);
}

void handle_right_redirection(t_redirect	redirection, t_pipe	*pipe)
{
	char **result;
	int fd;
	result = ft_split_lexer(redirection.left_str, ' ');
	result[0] = extract_command_name(result[0]);
	if (result[0] == NULL)
		return;
	pipe->cmd1 = result;
	pipe->cmd2 = NULL; //PAS DE DEUXIEME COMMANDE
	int	i = 0;
	while (result[i])
	{
		printf("Result %s\n", result[i++]);
	}
	fd = open(redirection.right_str, O_CREAT | O_WRONLY , 0666);
	if (pipe->fdout)
		pipe->fdin = pipe->fdout;
	else
		pipe->fdin = 1;
	pipe->fdout = fd;

	//close(fd);
	free(result);
}


void	manage_redirection(char *str, t_pipe	*pipe)
{
	int     	right;
	int     	left;
	char    	**result;
	int     	i;
	
	t_redirect	redirection;

	i = 0;
	right = string_has_right_redirection(str);
	left = string_has_left_redirection(str);
	printf("Right %d, left %d\n", right, left);
	while (right--)
	{
		result = ft_split_lexer(str, '>');
		redirection.left_str = result[i];
		redirection.right_str = result[i + 1];

		handle_right_redirection(redirection, pipe);
		//CALL PIPE HERE BUT CMD2 IS NULL. EX echo "HELLO" > a 
		free(result[i]);
		free(result[i + 1]);
		i++;
	}
	/*i = 0;
	while (left--)
	{
		result = ft_split_lexer(str, '<');
		redirection.left_str = result[i];
		redirection.right_str = result[i + 1];

		free(result[i]);
		free(result[i + 1]);
	}*/
}
