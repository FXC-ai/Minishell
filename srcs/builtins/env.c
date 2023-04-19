/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:17:52 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/19 12:43:50 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"


void	env_process(char **parsed_args, char *env[])
{
    int i;
    print_tab("env_process", parsed_args);

    if (size_tab(parsed_args) == 1)
    {
        i = 0;
        while (env[i])
        {
            printf("%s\n", env[i++]);
        }
    }
    else
    {
        global_sig.ms_errno = 127;
        perror("env");
    }
}