/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:39:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/16 23:32:58 by victorgiord      ###   ########.fr       */
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

void	disable_ctrl_chars(void)
{
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
}

int check_blank_line(char *line)
{
	int i;

	i = 0;
	while (is_space(line[i]))
	{
		i++;
	}
	if (line[i] == '\0')
	{
		return 0;
	}
	return 1;
}


int	check_entry(char *line)
{
	if (!line)
		return (0);
	if (ft_strlen(line) == 0)
		return (0);
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (0);
	add_history(line);
	if (check_blank_line(line) == 0)
		return (0);
	if (ft_strncmp(line, " ", ft_strlen(line)) == 0)
		return (0);
	return (1);
}

void	wait_for_input(char *env[])
{
	char	*line;

	signal_handler();
	while (42)
	{
		dup2(0,0);
		dup2(1,1);
		global_sig.program_in_process = 0;
		line = readline("minishell$ ");
		global_sig.program_in_process = 1;
		//disable_ctrl_chars();
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			//break ;
		}
		if (check_entry(line))
		{
			lexer(line, env);
		}
		free(line);
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
	ft_putstr_fd("END MAIN\n", 2);
	return (0);
}
