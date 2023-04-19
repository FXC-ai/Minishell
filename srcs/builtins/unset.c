/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:15:10 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/19 18:02:19 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

int unset_process(char **current_command)
{
	char    *key;
	size_t  len;
	int		i;
	char **new_env;

	

	new_env = malloc((size_tab(global_sig.env)) * sizeof(char *));
	if (new_env == NULL)
		return 0;


	key = current_command[1];
	len = ft_strlen(key);
	i = 0;
	while (current_command[1][i] != '\0' && current_command[1][i] != '=')
	{
		if (ft_isalnum(current_command[1][i]) == 0)
		{
			printf("export: `%s': not a valid identifier\n", current_command[1]);
			return (1);
		}
		i++;
	}

	i = 0;
	while (global_sig.env[i] != NULL)
	{
		if (ft_strncmp(global_sig.env[i], key, len) != 0)
		{
			new_env[i] = ft_strdup(global_sig.env[i]);
		}
		i++;
	}

	new_env[i] = NULL;
	free(global_sig.env);
	cpy_env(new_env);
	free(new_env);
	print_tab("ENV", global_sig.env);
	return (1);
}





/*int unset_process(char **current_command)
{
	char    *key;
	size_t  len;
	int		i;

	key = current_command[1];
	len = ft_strlen(key);

	print_tab("cuurent command", current_command);
	printf("len = %zu\n", len);


	i = 0;
	while (current_command[1][i] != '\0' && current_command[1][i] != '=')
	{
		if (ft_isalnum(current_command[1][i]) == 0)
		{
			printf("export: `%s': not a valid identifier\n", current_command[1]);
			return (1);
		}
		i++;
	}
	while (global_sig.env[i] != NULL)
	{
		if (ft_strncmp(global_sig.env[i], key, len) == 0 && env[i][len] == '=')
		{
			while (global_sig.env[i] != NULL)
			{
				env[i] = env[i + 1];
				i++;
			}
			break;
		}
		i++;
	}
	return (0);
}*/

int unset_process_str(char *key)
{
	size_t  len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (global_sig.env[i] != NULL)
	{
		if (ft_strncmp(global_sig.env[i], key, len) == 0 && global_sig.env[i][len] == '=')
		{
			while (global_sig.env[i] != NULL)
			{
				global_sig.env[i] = global_sig.env[i + 1];
				i++;
			}
			break;
		}
		i++;
	}
	return (0);
}