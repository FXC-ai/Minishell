/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:47:30 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 15:00:53 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static void	while_process(char *cmd, int *size_back, int *result)
{
	while (size_back > 0)
	{
		if (cmd[*size_back] == '\'')
		{
			(*result)--;
			break ;
		}
		if (cmd[*size_back] == '\"')
			break ;
		(*size_back)--;
	}
}

int	check_simple_quote(char *cmd, char *trimmed_command)
{
	int	size_cmd;
	int	size_trimmed_cmd;
	int	size_back;
	int	result;

	result = 2;
	size_cmd = ft_strlen(cmd);
	size_trimmed_cmd = ft_strlen(trimmed_command);
	size_back = size_cmd - size_trimmed_cmd;
	while_process(cmd, &size_back, &result);
	while (*trimmed_command != '\0')
	{
		if (*trimmed_command == '\'')
		{
			result--;
			break ;
		}
		if (cmd[size_back] == '\"')
			break ;
		trimmed_command++;
	}
	return (result);
}

int	check_simple_quote2(char *cmd, char *trimmed_command)
{
	int		i;
	int		in_quote;
	char	quote;

	quote = '\0';
	in_quote = 0;
	i = 0;
	while (&cmd[i] != trimmed_command)
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
		}
		i++;
	}
	return (in_quote && quote == '\'');
}
