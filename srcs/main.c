/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:39:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/15 17:25:27 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(int ac, char **argv, char **env)
{
	(void) argv;
	(void) env;
	(void) ac;
	char    *line;
	pid_t	child_pid;

	signal_handler();
	while(42)
	{
		line = readline("$ ");
		add_history(line);
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}	
		if (child_pid == 0)
		{
			lexer(line);
		}
		else
		{
			wait(0);
		}
	}
	return (0);
}