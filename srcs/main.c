/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:39:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/05 16:20:56 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_sig	global_sig;

void	sig_init(void)
{
	global_sig.sig_int = 0;
	global_sig.sig_quit = 0;
	global_sig.pid = 0;
	global_sig.ms_errno = 0;
}

void disable_ctrl_chars()
{
    struct termios attributes;

    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag &= ~ ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

int	check_entry(char *line)
{
	if (!line)
		return (0);
	if (ft_strlen(line) == 0)
		return (0);
	add_history(line);
	if (ft_strncmp(line, " ", ft_strlen(line)) == 0)
		return (0);
	return (1);
}

void	wait_for_input(char *env[])
{
	char    *line;
	signal_handler();
	while(42)
	{
		global_sig.program_in_process = 0;
		line = readline("minishell$ ");
		global_sig.program_in_process = 1;
		//disable_ctrl_chars();
		if (line == NULL)
		{
			write(1, "exit\n", 5);
            break;
        }
		
		if (check_entry(line))
		{
			fork{
				lexer(line, env);
			}
			
			

		}
	}
}

int	main(int ac, char **argv, char *env[])
{
	struct termios		tm;
	(void) argv;
	(void) ac;

	
	sig_init();
	if (tcgetattr(STDIN_FILENO, &tm) == -1)
		return (-1);
	tm.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tm) == -1)
		return (-1);
	wait_for_input(env);
	return (0);
}
