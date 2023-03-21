/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:15:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/21 16:07:01 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void handler(int sig)
{
    int is_interactive;

    is_interactive = isatty(STDIN_FILENO);
    //printf("Interactive %d\n", is_interactive);
    if (is_interactive)
    {
        if (sig == SIGINT)
        {
            rl_on_new_line();
            rl_replace_line("", 0);
            rl_redisplay();
            //write(STDOUT_FILENO, "\n$ ", 3);
        }
        if (sig == SIGQUIT)
        {
            //write(1, "NEpasquit\n", 10);
            //exit(EXIT_FAILURE);
        }
    }
    else
    {
        
    }
    
}

void signal_handler() {
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaddset(&sa.sa_mask, SIGQUIT);

    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}