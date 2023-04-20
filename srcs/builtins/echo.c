/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:11:00 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/20 11:42:17 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"


void echo_process(char **current_command)
{
	int	i;
	int has_flag;
	int nbr_tokens;

	i = 1;
	has_flag = 0;
	nbr_tokens = size_tab(current_command) - 1;

	if (ft_strcmp(current_command[i], "-n") == 0)
	{			
		has_flag = 1;
		i++;
	}		

	//printf("nbr_tokens = %d || has_flag = %d\n", nbr_tokens, has_flag);

	if (nbr_tokens == 0)
	{
		//printf("cas 1\n");
		printf("\n");
	}
	else if (nbr_tokens > 1 && has_flag == 1)
	{
		//printf("cas 2\n");
		printf("%s", current_command[i++]);
		while (current_command[i])
		{
			printf(" %s", current_command[i]);
			i++;
		}
	}
	else if (nbr_tokens >= 1 && has_flag == 0)
	{
		//printf("cas 3\n");
		printf("%s", current_command[i++]);
		while (current_command[i])
		{
			printf(" %s", current_command[i]);
			i++;
		}
		printf("\n");
	}
}