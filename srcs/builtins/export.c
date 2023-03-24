/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:32:31 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/24 16:26:14 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void export_process(char **current_command, char *env[])
{
	int i;

	i = 0;
	(void) current_command;
	(void) env;
	if (current_command[1] == NULL)
	{
		while (env[i])
		{
			printf("declare -x %s\n", env[i]);
			i++;
		}
	}
	else
	{
		
	}
}
