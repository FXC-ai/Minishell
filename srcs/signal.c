/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:15:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/19 18:29:13 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		if (global_sig.program_in_process == 0)
			rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		if (global_sig.program_in_process == 1)
		{
			write(1, "Quit\n", 5);
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	signal_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
