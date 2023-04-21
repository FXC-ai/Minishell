/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:50 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 11:37:08 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

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
			perror("cd");
			return ;
		}
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			ligne = ft_strjoin("PWD=", cwd);
			ft_unset("PWD");
			ft_export(ligne);
			free(ligne);
			ligne = ft_strjoin("OLDPWD=", temp);
			ft_unset("OLDPWD");
			ft_export(ligne);
			free(ligne);
		}		
	}
}
