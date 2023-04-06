/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:37:57 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/06 11:42:27 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	**create_tab_paths(char *env[])
{
	int		i;
	char	*paths;
	char	**paths_tab;

	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], "PATH", 4) == 0)
			paths = ft_substr(env[i], 5, ft_strlen(env[i]) - 4);
		i++;
	}
	paths_tab = ft_split(paths, ':');
	free(paths);
	paths = NULL;
	return (paths_tab);
}

static char	*create_path_cmd(char *path, char *cmd)
{
	char	*tmp;
	char	*path_cmd;

	tmp = ft_strjoin(path, "/");
	path_cmd = ft_strjoin(tmp, cmd);
	free(tmp);
	tmp = NULL;
	return (path_cmd);
}

static char	*cmd_exists(char *cmd, char *env[])
{
	int		i;
	char	**tab_paths;
	char	*path_to_test;

	tab_paths = create_tab_paths(env);
	i = 0;
	while (tab_paths[i])
	{
		path_to_test = create_path_cmd(tab_paths[i], cmd);
		if (access(path_to_test, F_OK) == 0)
		{
			ft_free_tabs(tab_paths, size_tab(tab_paths));
			return (path_to_test);
		}
		free(path_to_test);
		path_to_test = NULL;
		i++;
	}
	ft_free_tabs(tab_paths, size_tab(tab_paths));
	return (NULL);
}

static char *extract_command_name(const char *full_path)
{
	//F_OK = LE FICHIER EXITSTE, X_OK LE FICHIER EST EXECUTABLE
	if (full_path == NULL || access(full_path, F_OK | X_OK) != 0)
	{
		return NULL;
	}
	const char *last_slash = strrchr(full_path, '/');
	if (last_slash == NULL)
	{
		return strdup(full_path);
	} 
	else
	{
		return strdup(last_slash + 1);
	}
	//faudra free result
}

char *normalize_cmd(char* str, char *env[])
{	
	char *result;

	if (str == NULL || str[0] == '\0')
		return str;
	// Cas ou la commande est envoyée sous forme de chemin
	if (ft_strchr(str, '/') != NULL)
	{
		result = extract_command_name(str);
		if (result == NULL)
		{
			return (NULL);
		}
		return cmd_exists(result, env);
	}
	
	// Cas ou la commande est envoyée sans chemin
	return cmd_exists(str, env);
}