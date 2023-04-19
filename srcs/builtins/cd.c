/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:50 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/19 13:55:59 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void cd_process(char **parsed_args, char *env[])
{
    char cwd[4096];
    char *ligne;
    char temp[4096];

    (void) env;
    getcwd(temp, sizeof(cwd));
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
                ligne = ft_strjoin("OLDPWD=", temp);
                add_to_env(ligne, temp, env);
                free(ligne);
                
            }
        }
    }
}
