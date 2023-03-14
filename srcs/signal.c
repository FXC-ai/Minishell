/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:15:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/14 15:56:58 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void handler(int sig)
{
    if (sig == SIGINT)
        exit(EXIT_FAILURE);
    if (sig == EOF)
    {
        sleep(1);
        printf("EOF \n");
        exit(EXIT_FAILURE);
    }
    if (sig == SIGQUIT)
    {
        printf("\nzsh: suspended \n");
        exit(EXIT_FAILURE);
    }
}

void    signal_handler()
{
    struct sigaction	sa;
    
    sa.sa_handler = handler;
    sigaction(SIGINT, &sa, NULL);
    sigaction(EOF, &sa, NULL);
	sigaction(SIGQUIT , &sa, NULL);
}