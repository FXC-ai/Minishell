/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:50 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/25 13:39:13 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

static void	unsetexport(char *key, char *ligne)
{
	ft_unset(key);
	ft_export(ligne);
}

void	cd_process(char **parsed_args)
{
	char	cwd[4096];
	char	*ligne;
	char	temp[4096];

	getcwd(temp, sizeof(cwd));
	if (parsed_args[1] == NULL)
		return ;
	else
	{
		if (chdir(parsed_args[1]) != 0)
		{
			g_env.ms_errno = 1;
			perror("cd");
		}
		else if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			ligne = ft_strjoin("PWD=", cwd);
			unsetexport("PWD", ligne);
			free(ligne);
			ligne = ft_strjoin("OLDPWD=", temp);
			unsetexport("OLDPWD", ligne);
			free(ligne);
		}
	}
}
