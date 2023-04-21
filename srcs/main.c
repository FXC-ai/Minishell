/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:39:22 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/21 11:11:27 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_sig	g_env;

void	sig_init(void)
{
	g_env.sig_int = 0;
	g_env.sig_quit = 0;
	g_env.pid = 0;
	g_env.ms_errno = 0;
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
		g_env.program_in_process = 0;
		line = readline("minishell$ ");
		g_env.program_in_process = 1;
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
	g_env.env = malloc(sizeof(char *) * (size_env + 1));
	if (g_env.env == NULL)
		return ;
	i = 0;
	while (i < size_env)
	{
		g_env.env[i] = ft_strdup(env[i]);
		i++;
	}
	g_env.env[i] = NULL;
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
