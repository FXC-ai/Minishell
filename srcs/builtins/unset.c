/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:15:10 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/30 18:00:31 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int unset_process(char **current_command, char *env[])
{
	char    *key;
	size_t  len;
	int		i;

	key = current_command[1];
	len = ft_strlen(key);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
		{
			while (env[i] != NULL)
			{
				env[i] = env[i + 1];
				i++;
			}
			break;
		}
		i++;
	}
	return (0);
}

int unset_process_str(char *key, char *env[])
{
	size_t  len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
		{
			while (env[i] != NULL)
			{
				env[i] = env[i + 1];
				i++;
			}
			break;
		}
		i++;
	}
	return (0);
}