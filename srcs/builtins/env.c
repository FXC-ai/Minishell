/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 17:17:52 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/30 18:33:54 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/header.h"

void	env_process(char **parsed_args, char *env[])
{
    (void) parsed_args;
   // int i;
    int i;

   // i = 0;
    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i++]);
    }
    
}