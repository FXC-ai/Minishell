/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:00:40 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 17:55:27 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	process2(t_utils *u, char *tab_cmd)
{
	if (u->in_quote == 0)
	{
		u->quote = tab_cmd[u->i];
		u->in_quote = 1;
	}
	else if (tab_cmd[u->i] == u->quote)
		u->in_quote = 0;
}

int	is_valid_chevron(char *tab_cmd, char chev_type)
{
	t_utils	u;

	init_utils(&u);
	while (tab_cmd[u.i] != '\0')
	{
		if (tab_cmd[u.i] == '\'' || tab_cmd[u.i] == '\"')
		{
			process2(&u, tab_cmd);
		}
		if (tab_cmd[u.i] == chev_type && u.in_quote == 0)
		{
			if (tab_cmd[u.i + 1] == chev_type)
				u.i++;
			u.i++;
			while (is_space(tab_cmd[u.i]) == 1)
				u.i++;
			if (is_chevron(tab_cmd[u.i]) == 1)
				return (-1);
			u.count++;
		}
		u.i++;
	}
	return (u.count);
}

char	check_redirections(char *str, char type_chev)
{
	int	i;

	i = 1;
	if (str[i] == type_chev)
		i++;
	while (is_space(str[i]) && str[i] != '\0')
		i++;
	if (is_chevron(str[i]))
		return (str[i]);
	if (str[i] == '\0')
		return (str[i]);
	return (1);
}

static int	lexer_p(t_parsed_args **cmd_red_lst, int *in_out_fd)
{
	if (cmd_red_lst[1] == NULL)
	{
		if (process_single_command(cmd_red_lst, in_out_fd) == -1)
			return (-1);
	}
	else
	{
		if (process_multiple_commands(cmd_red_lst) == -1)
			return (-1);
	}
	free(in_out_fd);
	free_struct(cmd_red_lst);
	return (1);
}

int	lexer(char *str)
{
	char			**result;
	char			c;
	int				i;
	int				*in_out_fd;
	t_parsed_args	**cmd_red_lst;

	c = '|';
	in_out_fd = malloc(2 * sizeof(int));
	if (in_out_fd == NULL)
		return (0);
	i = 0;
	result = ft_split_lexer(str, c);
	if (check_redirections_process(result) == 0)
	{
		free(in_out_fd);
		freemalloc(result, size_tab(result));
		return (1);
	}
	parse_dollar(result);
	cmd_red_lst = init_parsed_args(result);
	freemalloc(result, size_tab(result));
	in_out_fd[0] = STDIN_FILENO;
	in_out_fd[1] = STDOUT_FILENO;
	lexer_p(cmd_red_lst, in_out_fd);
	return (1);
}
