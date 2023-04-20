/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:15:28 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/20 22:01:37 by victorgiord      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	remove_quote_in_tab(char **tab) {
	int i;
	int	j;
	char *line;
	char *new_line;

	i = 0;
	while (tab[i])
	{
		line = tab[i];
		new_line = malloc(strlen(line) + 1);
		int new_line_idx = 0;
		bool inside_single_quote = false;
		bool inside_double_quote = false;
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
