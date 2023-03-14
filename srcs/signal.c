/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:15:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/14 13:44:56 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/header.h"

static void handler(int sig)
{
    if (sig == SIGINT)
        exit(0);
}

void    signal_handler()
{
    struct sigaction	sa;
    
    sa.sa_handler = handler;
    sigaction(SIGINT, &sa, NULL);
	//sigaction(SIGQUIT , &sa, NULL);
}