/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:11:00 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 15:47:51 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static void	process(char **current_command, int i, int nb_t, int has_flag)
{
	if (ft_strcmp(current_command[i], "-n") == 0)
	{			
		has_flag = 1;
		i++;
	}
	if (nb_t == 0)
		printf("\n");
	else if (nb_t > 1 && has_flag == 1)
	{
		printf("%s", current_command[i++]);
		while (current_command[i])
			printf(" %s", current_command[i++]);
	}
	else if (nb_t >= 1 && has_flag == 0)
	{
		printf("%s", current_command[i++]);
		while (current_command[i])
		{
			printf(" %s", current_command[i]);
			i++;
		}
		printf("\n");
	}
}

void	echo_process(char **current_command)
{
	int	i;
	int	has_flag;
	int	nbr_tokens;

	i = 1;
	has_flag = 0;
	nbr_tokens = size_tab(current_command) - 1;
	process(current_command, i, nbr_tokens, has_flag);
}
