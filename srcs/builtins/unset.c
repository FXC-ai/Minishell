/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:15:10 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/20 13:59:04 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static int ft_unset(char *token)
{
	char    *key;
	size_t  len;
	int		i;
	int		j;
	char **new_env;


	new_env = malloc((size_tab(global_sig.env) + 1 - 1) * sizeof(char *));
	if (new_env == NULL)
		return 0;


	key = token;
	len = ft_strlen(key);
	i = 0;
	while (token[i] != '\0' && token[i] != '=')
	{
		if (ft_isalnum(token[i]) == 0)
		{
			printf("export: `%s': not a valid identifier\n", token);
			return (1);
		}
		i++;
	}

	i = 0;
	j = 0;
	while (global_sig.env[i] != NULL)
	{
		//printf("ft_stncmp = %d && global_sig.env[i][%zu]\n", ft_strncmp(global_sig.env[i], key, len), len);
		if (ft_strncmp(global_sig.env[i], key, len) != 0 || global_sig.env[i][len] != '=')
		{
			new_env[j] = ft_strdup(global_sig.env[i]);
			//printf("new_env[%d] = %s\n", j, new_env[j]);
			//usleep(250000);
			j++;
		}
		i++;
	}

	new_env[j] = NULL;
	freemalloc(global_sig.env, size_tab(global_sig.env));
	global_sig.env = NULL;
	print_tab("new env", new_env);
	cpy_env(new_env);
	freemalloc(new_env, size_tab(global_sig.env));
	//print_tab("ENV", global_sig.env);
	return (1);
}

int unset_process (char **parsed_args)
{
	int i;

	if (parsed_args[1] == NULL)
	{
		return (1);
	}
	
	i = 1;
	while (parsed_args[i] != NULL)
	{
		printf("parsed_args[%d] = %s\n",i, parsed_args[i]);
		ft_unset(parsed_args[i]);
		i++;
	}

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