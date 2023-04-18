/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:50 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/18 16:06:41 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void cd_process(char **parsed_args, char *env[])
{
    char cwd[4096];
    char *ligne;
    (void) env;

    if (parsed_args[1] == NULL) 
    {
        return;
    }
    else 
    {
        if (chdir(parsed_args[1]) != 0)
        {
            perror("cd");
            return;
        }
        else
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                ligne = ft_strjoin("PWD=", cwd);
                add_to_env(ligne, cwd, env);
                free(ligne);
            }
        }
    }
}
