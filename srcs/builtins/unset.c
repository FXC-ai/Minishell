/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:15:10 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/20 18:29:11 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static char	**alloc_env(char ***new_env, char *token)
{
	if (key_already_exist(token) == 1)
	{
		*new_env = malloc((size_tab(global_sig.env)) * sizeof(char *));
	}
	else
		*new_env = malloc((size_tab(global_sig.env) + 1) * sizeof(char *));
	if (*new_env == NULL)
		return (NULL);
	return (*new_env);
}

static int	is_valid(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '\0' && token[i] != '=')
	{
		if (ft_isalnum(token[i]) == 0)
		{
			printf("export: `%s': not a valid identifier\n", token);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(char *token)
{
	size_t	len;
	int		i;
	int		j;
	char	**new_env;

	if (alloc_env(&new_env, token) == NULL)
		exit(errno);
	len = ft_strlen(token);
	if (is_valid(token) == 0)
		return (1);
	i = 0;
	j = 0;
	while (global_sig.env[i] != NULL)
	{
		if (ft_strncmp(global_sig.env[i], token, len) != 0
			|| global_sig.env[i][len] != '=')
			new_env[j++] = ft_strdup(global_sig.env[i]);
		i++;
	}
	new_env[j] = NULL;
	freemalloc(global_sig.env, size_tab(global_sig.env));
	global_sig.env = NULL;
	cpy_env(new_env);
	freemalloc(new_env, size_tab(global_sig.env));
	return (1);
}

int	unset_process(char **parsed_args)
{
	int	i;

	if (parsed_args[1] == NULL)
	{
		return (1);
	}
	i = 1;
	while (parsed_args[i] != NULL)
	{
		ft_unset(parsed_args[i]);
		i++;
	}
	return (1);
}

int	unset_process_str(char *key)
{
	size_t	len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (global_sig.env[i] != NULL)
	{
		if (ft_strncmp(global_sig.env[i], key, len) == 0
			&& global_sig.env[i][len] == '=')
		{
			while (global_sig.env[i] != NULL)
			{
				global_sig.env[i] = global_sig.env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
	return (0);
}
