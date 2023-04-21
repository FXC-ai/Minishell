/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:32:31 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 11:33:20 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	add_to_env(char *ligne, char *value)
{
	char	*result;
	int		i;
	int		j;
	char	**s_result;

	s_result = ft_split(ligne, '=');
	unset_process_str(s_result[0]);
	i = 0;
	j = 0;
	result = malloc(ft_strlen(value) + ft_strlen(ligne) + 2);
	if (result == NULL)
		return ;
	while (i < (int)ft_strlen(ligne) && ligne[i] != '=')
		result[j++] = ligne[i++];
	result[j++] = '=';
	i = 0;
	while (i < (int)ft_strlen(value))
		result[j++] = value[i++];
	result[j] = '\0';
	i = 0;
	while (g_env.env[i])
		i++;
	g_env.env[i] = result;
	g_env.env[i + 1] = NULL;
	freemalloc(s_result, size_tab(s_result));
}

void	ft_export(char *token)
{
	char	**new_env;
	int		i;
	char	*key;

	key = get_key_from_token(token);
	i = 0;
	if (key_already_exist(key) == 1)
		new_env = malloc((size_tab(g_env.env) + 1) * sizeof(char *));
	else
		new_env = malloc((size_tab(g_env.env) + 2) * sizeof(char *));
	ft_unset(key);
	free(key);
	while (g_env.env[i])
	{
		new_env[i] = ft_strdup(g_env.env[i]);
		i++;
	}
	new_env[i] = ft_strdup(token);
	new_env[i + 1] = NULL;
	freemalloc(g_env.env, size_tab(g_env.env));
	cpy_env(new_env);
	freemalloc(new_env, size_tab(new_env));
}

void	print_export(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_env.env[i])
	{
		j = 0;
		printf("declare -x ");
		while (g_env.env[i][j] && g_env.env[i][j] != '=')
		{
			printf("%c", g_env.env[i][j]);
			j++;
		}
		if (g_env.env[i][j] == '=')
		{
			printf("=");
			printf("\"");
			j++;
			while (g_env.env[i][j])
				printf("%c", g_env.env[i][j++]);
		}
		printf("\"");
		printf("\n");
		i++;
	}
}

static int	check_entry_export(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[0] == '=')
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(token, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_env.ms_errno = 1;
			return (0);
		}
		if (ft_strlen(token) <= 1)
			return (0);
		if (token[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	export_process(char **parsed_args)
{
	int	i;

	i = 0;
	if (parsed_args[1] == NULL)
		print_export();
	else
	{
		i = 1;
		while (parsed_args[i] != NULL)
		{
			if (check_entry_export(parsed_args[i]) == 1)
			{
				ft_export(parsed_args[i]);
			}
			i++;
		}
	}
}
