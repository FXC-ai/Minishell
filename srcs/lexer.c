/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:32:28 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/21 16:56:49 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	my_error()
{
	exit(EXIT_FAILURE);
}

char **lexer(char *str, char *env[])
{
	char	**result;
	int		i;
	char	c = '|';
	i = 0;
	result = ft_split_lexer(str, c);
	/*while (result[i])
	{
		//printf("str %d = [%s]\n", i, result[i]);
		i++;
	}*/
	parsing(result, env);
	return (result);
}