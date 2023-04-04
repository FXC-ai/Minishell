/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:27:27 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/04 18:24:20 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void pwd_process()
{
    char cwd[4096];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
        printf("%s\n", cwd);
    } 
    else 
    {
        perror("getcwd");
    }
}