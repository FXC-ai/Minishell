/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:39:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/20 22:04:42 by victorgiord      ###   ########.fr       */
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

int	check_blank_line(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
	{
		i++;
	}
	if (line[i] == '\0')
	{
		return (0);
	}
	return (1);
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
	if (check_quotes(line) == 0)
		return (0);
	if (ft_strncmp(line, " ", ft_strlen(line)) == 0)
		return (0);
	return (1);
}

void	wait_for_input(void)
{
	char	*line;

	signal_handler();
	while (42)
	{
		dup2(0, 0);
		dup2(1, 1);
		global_sig.program_in_process = 0;
		line = readline("minishell$ ");
		global_sig.program_in_process = 1;
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (check_entry(line))
		{
			lexer(line);
		}
		free(line);
	}
}

void	cpy_env(char **env)
{
	int		size_env;
	int		i;

	size_env = size_tab(env);
	global_sig.env = malloc(sizeof(char *) * (size_env + 1));
	if (global_sig.env == NULL)
		return ;
	i = 0;
	while (i < size_env)
	{
		global_sig.env[i] = ft_strdup(env[i]);
		i++;
	}
	global_sig.env[i] = NULL;
}

int	main(int ac, char **argv, char *env[])
{
	struct termios		tm;

	cpy_env(env);
	(void) argv;
	(void) ac;
	sig_init();
	if (tcgetattr(STDIN_FILENO, &tm) == -1)
		return (-1);
	tm.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tm) == -1)
		return (-1);
	wait_for_input();
	return (0);
}
