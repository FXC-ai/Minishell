/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:37:57 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/20 15:54:31 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char	**create_tab_paths()
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

/*static char *extract_command_name(const char *full_path)
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
}*/

char *normalize_cmd(char* str)
{	
	//char *result;

	if (str == NULL || str[0] == '\0')
		return str;
	// Cas ou la commande est envoyée sous forme de chemin
	if (ft_strchr(str, '/') != NULL)
	{
		return str;
	}
	
	// Cas ou la commande est envoyée sans chemin
	return cmd_exists(str);
}