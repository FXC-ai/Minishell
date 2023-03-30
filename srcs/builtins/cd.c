/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:50 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/30 12:41:53 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void cd_process(char **current_command) {

    print_tab(current_command);
    chdir("/Users/fcoindre");
    exit(1);
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