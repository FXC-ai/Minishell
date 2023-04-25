/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:53:34 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/25 13:23:15 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	init_utils(t_utils *u)
{
	u->i = 0;
	u->j = 0;
	u->in_quote = 0;
	u->in_word = 0;
	u->quote = '\0';
	u->start = 0;
	u->count = 0;
}

int	chr_is_in_quote(char *str, int ind_char)
{
	int		i;
	int		in_quote;
	char	quote;

	if ((size_t) ind_char > ft_strlen(str))
		return (-1);
	in_quote = 0;
	quote = '\0';
	i = 0;
	while (i < ind_char)
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quote == 0)
			{
				quote = str[i];
				in_quote = 1;
			}
			else if (str[i] == quote)
				in_quote = 0;
		}
		i++;
	}
	return (in_quote);
}

static void	process(char chk_char)
{
	g_env.ms_errno = 258;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (is_chevron(chk_char))
	{
		ft_putchar_fd(chk_char, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd("newline'\n", 2);
	}
}

int	check_redirections_process(char **tab_cmds)
{
	int		i;
	int		j;
	char	chk_char;

	i = 0;
	while (tab_cmds[i] != NULL)
	{
		j = 0;
		while (tab_cmds[i][j] != '\0')
		{
			if (is_chevron(tab_cmds[i][j])
				&& chr_is_in_quote(tab_cmds[i], j) == 0)
			{
				chk_char = check_redirections(tab_cmds[i] + j, tab_cmds[i][j]);
				if (chk_char != 1)
				{
					process(chk_char);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}
