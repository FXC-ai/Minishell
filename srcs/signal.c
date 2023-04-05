/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:15:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/05 15:51:05 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void handler(int sig)
{
    if (sig == SIGINT)//Ctrl + c
    {
       // sleep(1);
        ft_putstr_fd("\n", 1);
        rl_replace_line("", 0);
        if (global_sig.program_in_process == 0)
            rl_on_new_line();
        rl_redisplay();
        global_sig.sig_int = 1;

    }
    if (sig == SIGQUIT) //Ctrl + '\'
    {
        rl_on_new_line();
        rl_redisplay();
        global_sig.sig_quit = 1;
        //write(1, "NEpasquit\n", 10);
        //exit(EXIT_FAILURE);
    }
}

void signal_handler() 
{
    struct sigaction sa;

    /*sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaddset(&sa.sa_mask, SIGQUIT);*/

    sa.sa_handler = handler;
    //sa.sa_flags = SA_RESTART;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}