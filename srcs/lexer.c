/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:32:28 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/14 18:51:14 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"


/*static	int count_char(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}*/

void	my_error()
{
	exit(EXIT_FAILURE);
}

char **lexer(char *str)
{
	char	**result;
	int		i;

	i = 0;
	/*if (count_char(str, '\'') % 2 || count_char(str, '"') % 2)
	{
		my_error();
	}*/
	result = ft_split_lexer(str);
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	return (result);
}