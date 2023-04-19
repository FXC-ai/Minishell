/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:17:52 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/19 17:56:00 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"


void	env_process(char **parsed_args)
{
    int i;

    if (size_tab(parsed_args) == 1)
    {
        i = 0;
        while (global_sig.env[i])
        {
            printf("%s\n", global_sig.env[i++]);
        }
    }
    else
    {
        global_sig.ms_errno = 127;
        perror("env");
    }
}