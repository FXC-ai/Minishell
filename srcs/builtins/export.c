/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:32:31 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/24 15:40:46 by vgiordan         ###   ########.fr       */
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
	/*else
	{
		// Sinon, ajouter ou modifier la variable d'environnement spécifiée
		char *key = strtok(current_command[1], "=");
		char *value = strtok(NULL, "=");

		if (key == NULL || value == NULL) {
			fprintf(stderr, "export: invalid format, use KEY=VALUE\n");
			return;
		}

		if (setenv(key, value, 1) != 0) {
			perror("setenv");
		}
	}*/
}
