/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:35:07 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/29 17:18:57 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/header.h"


void	print_tab(char **tab)
{
	int i;

	i = 0;
	printf("--------------TAB------------\n");
	while (tab[i])
	{
		printf("%s\n", tab[i++]);
	}
}

int	is_builtins(char *str)
{
	
	if (ft_strncmp(str, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(str, "cd", 2) == 0)
		return (2);
	if (ft_strncmp(str, "pwd", 3) == 0)
		return (3);
	if (ft_strncmp(str, "export", 6) == 0)
		return (4);
	if (ft_strncmp(str, "unset", 5) == 0)
		return (5);
	if (ft_strncmp(str, "env", 3) == 0)
		return (6);
	if (ft_strncmp(str, "exit", 4) == 0)
		return (7);
	return (0);
}

void	ft_free_tabs(char **tab, int h)
{
	int	i;

	i = 0;
	while (i <= h)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	size_tab(char **tab)
{
	int	count;

	count = 0;
	while (tab[count] != NULL)
		count++;
	return (count);
}

char	**create_tab_paths(char *env[])
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

char	*create_path_cmd(char *path, char *cmd)
{
	char	*tmp;
	char	*path_cmd;

	tmp = ft_strjoin(path, "/");
	path_cmd = ft_strjoin(tmp, cmd);
	free(tmp);
	tmp = NULL;
	return (path_cmd);
}

char	*cmd_exists(char *cmd, char *env[])
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

char *extract_command_name(const char *full_path)
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

/*
int main(int argc, char const *argv[], char *env[])
{

	char *str = "/binkjhkjhjkh/ls -la";
	char *str1 = "ls";
	char *str2 = "/bin/ls -la";

	char **tab_cmd = ft_split(str, ' ');

	//char *test_extract_line = extract_command_name(str2);
	//char *test_cmd_exists = cmd_exists(str2, env);

	char *r = normalize_cmd(tab_cmd[0], env);


	printf("R= %s\n", r);

	ft_free_tabs(tab_cmd, size_tab(tab_cmd));


	return 0;
}*/

