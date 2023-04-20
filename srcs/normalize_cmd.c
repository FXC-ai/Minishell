/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:37:57 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/20 21:37:39 by victorgiord      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	**create_tab_paths(void)
{
	int		i;
	char	*paths;
	char	**paths_tab;

	i = 0;
	paths = NULL;
	paths_tab = NULL;
	while (global_sig.env[i])
	{
		if (strncmp(global_sig.env[i], "PATH", 4) == 0)
			paths = ft_substr(global_sig.env[i], 5, ft_strlen(global_sig.env[i]) - 4);
		i++;
	}
	if (paths != NULL)
	{
		paths_tab = ft_split(paths, ':');
		free(paths);
	}
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

static char	*cmd_exists(char *cmd)
{
	int		i;
	char	**tab_paths;
	char	*path_to_test;

	tab_paths = create_tab_paths();
	if (tab_paths == NULL)
		return (NULL);
	i = 0;
	while (tab_paths[i])
	{
		path_to_test = create_path_cmd(tab_paths[i], cmd);
		if (access(path_to_test, F_OK) == 0)
		{
			freemalloc(tab_paths, size_tab(tab_paths));
			return (path_to_test);
		}
		free(path_to_test);
		path_to_test = NULL;
		i++;
	}
	freemalloc(tab_paths, size_tab(tab_paths));
	return (NULL);
}

char	*normalize_cmd(char *str)
{	
	if (str == NULL || str[0] == '\0')
		return (str);
	// Cas ou la commande est envoyée sous forme de chemin
	if (ft_strchr(str, '/') != NULL)
	{
		return (str);
	}
	// Cas ou la commande est envoyée sans chemin
	return (cmd_exists(str));
}
