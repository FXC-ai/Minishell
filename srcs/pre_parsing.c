/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:02:00 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 12:54:43 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	check_quotes(char *str)
{
	int		in_quote;
	char	quote;
	int		i;

	i = 0;
	in_quote = 0;
	quote = '\0';
	while (str[i])
	{
		if (in_quote == 0 && is_quote(str[i]))
		{
			quote = str[i];
			in_quote = 1;
		}
		else if (in_quote == 1 && str[i] == quote)
		{
			in_quote = 0;
			quote = '\0';
		}
		i++;
	}
	if (in_quote == 0)
		return (1);
	printf("Please close \" or \'\n");
	return (0);
}

int	check_blank_line(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
	{
		i++;
	}
	if (line[i] == '\0')
	{
		return (0);
	}
	return (1);
}

int	check_entry(char *line)
{
	if (!line)
		return (0);
	if (ft_strlen(line) == 0)
		return (0);
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (0);
	add_history(line);
	if (check_blank_line(line) == 0)
		return (0);
	if (check_quotes(line) == 0)
		return (0);
	if (ft_strncmp(line, " ", ft_strlen(line)) == 0)
		return (0);
	return (1);
}
