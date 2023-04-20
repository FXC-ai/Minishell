/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:02:00 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/19 18:35:50 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

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
