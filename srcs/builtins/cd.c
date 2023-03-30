/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:50 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/30 14:23:39 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void cd_process(char **current_command)
{
    if (current_command[1] == NULL) 
    {
        return;
    }
    else 
    {
        if (chdir(current_command[1]) != 0) 
        {
            perror("cd");
            return;
        }
    }
}