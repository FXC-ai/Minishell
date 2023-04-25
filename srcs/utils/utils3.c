/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:15:28 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/25 13:23:10 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	remove_quotes_from_line(char *line)
{
	int		j;
	int		new_line_idx;
	bool	inside_single_quote;
	bool	inside_double_quote;
	char	*new_line;

	new_line = malloc(strlen(line) + 1);
	new_line_idx = 0;
	inside_single_quote = false;
	inside_double_quote = false;
	j = 0;
	while (line[j])
	{
		if (line[j] == '\'' && !inside_double_quote)
			inside_single_quote = !inside_single_quote;
		else if (line[j] == '\"' && !inside_single_quote)
			inside_double_quote = !inside_double_quote;
		else
			new_line[new_line_idx++] = line[j];
		j++;
	}
	new_line[new_line_idx] = '\0';
	ft_strlcpy(line, new_line, ft_strlen(line) + 1);
	free(new_line);
}

void	remove_quote_in_tab(char **tab)
{
	int		i;
	char	*line;

	i = 0;
	while (tab[i])
	{
		line = tab[i];
		remove_quotes_from_line(line);
		i++;
	}
}

void	print_command_not_found(char *str)
{
	write(2, str, ft_strlen(str));
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

int	is_chevron(char c)
{
	return (c == '>' || c == '<');
}

int	count_chr(char *str, char c)
{
	int		count;
	int		i;
	int		in_quote;
	char	quote;

	count = 0;
	i = 0;
	in_quote = 0;
	quote = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == c && in_quote == 0)
			count++;
		if (is_quote(str[i]) == 1 && in_quote == 0)
		{
			in_quote = 1;
			quote = str[i++];
		}
		if (str[i] == quote && in_quote == 1)
			in_quote = 0;
		i++;
	}
	if (str[i - 1] != c)
		count++;
	return (count);
}
