/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:32:28 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/14 15:53:47 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

char **lexer(char *str)
{
	char	**result;
	int		i;

	i = 0;
	result = ft_split(str, ' ');
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	return (result);
}