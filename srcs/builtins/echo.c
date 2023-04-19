/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:11:00 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/19 18:13:04 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"


void echo_process(char **current_command)
{
	int	i;
	int has_flag;
	int nbr_tokens;

	nbr_tokens = size_tab(current_command) - 1;
	if (nbr_tokens == 0)
		printf("\n");
	else
	{
		i = 1;
		has_flag = 0;
		if (ft_strcmp(current_command[i], "-n") == 0)
		{
			has_flag = 1;
			i++;
		}
		printf("%s", current_command[i++]);
		while (current_command[i])
		{
			printf(" %s", current_command[i]);
			i++;
		}
		if (has_flag == 0) 
			printf("\n");
	}
}