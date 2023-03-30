/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:11:00 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/30 12:58:43 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void echo_process(char **current_command)
{
	int	i;
	int has_flag;

	ft_putstr_fd("CA marche 3\n", 2);
	i = 1;
	has_flag = 0;
	if (ft_strcmp(current_command[i], "-n") == 0)
	{
		has_flag = 1;
		i++;
	}
    while (current_command[i])
	{
		ft_putstr_fd("CA marche 4\n", 2);
		printf("%s", current_command[i]);
		i++;
    }
    if (has_flag == 0) 
	{
        printf("\n");
    }
}