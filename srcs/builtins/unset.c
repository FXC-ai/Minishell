/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:15:10 by vgiordan          #+#    #+#             */
/*   Updated: 2023/05/02 11:55:11 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static char	**alloc_env(char ***new_env, char *token)
{
	if (key_already_exist(token) == 1)
	{
		*new_env = malloc((size_tab(g_env.env)) * sizeof(char *));
	}
	else
		*new_env = malloc((size_tab(g_env.env) + 1) * sizeof(char *));
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
			g_env.ms_errno = 1;
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

	if (is_valid(token) == 0)
		return (1);
	if (alloc_env(&new_env, token) == NULL)
		exit(errno);
	len = ft_strlen(token);
	i = 0;
	j = 0;
	while (g_env.env[i] != NULL)
	{
		if (ft_strncmp(g_env.env[i], token, len) != 0
			|| g_env.env[i][len] != '=')
			new_env[j++] = ft_strdup(g_env.env[i]);
		i++;
	}
	new_env[j] = NULL;
	freemalloc(g_env.env, size_tab(g_env.env));
	g_env.env = NULL;
	cpy_env(new_env);
	freemalloc(new_env, size_tab(g_env.env));
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
	while (g_env.env[i] != NULL)
	{
		if (ft_strncmp(g_env.env[i], key, len) == 0
			&& g_env.env[i][len] == '=')
		{
			while (g_env.env[i] != NULL)
			{
				g_env.env[i] = g_env.env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
	return (0);
}
