/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:37:57 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/21 12:10:05 by vgiordan         ###   ########.fr       */
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
	while (g_env.env[i])
	{
		if (strncmp(g_env.env[i], "PATH", 4) == 0)
			paths = ft_substr(g_env.env[i], 5, ft_strlen(g_env.env[i]) - 4);
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
	if (ft_strchr(str, '/') != NULL)
	{
		return (str);
	}
	return (cmd_exists(str));
}
