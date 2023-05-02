/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:49:47 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/02 14:42:24 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	size_struct(t_parsed_args **s)
{
	int	i;

	if (s == NULL || *s == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	execute_first_command(char **cmd, int *in_out_fd, int pipe_fd[], int check_red)
{
	g_env.pid = fork();
	if (g_env.pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (check_red == 1)
			execute_command(cmd, in_out_fd[0], in_out_fd[1]);
		exit (0);
	}
}

void	ex_m_cm(char **cmd, int *in_out_fd, int pipe_fd_in[], int pipe_fd_out[], int check_red)
{
	g_env.pid = fork();
	if (g_env.pid == 0)
	{
		dup2(pipe_fd_in[0], STDIN_FILENO);
		dup2(pipe_fd_out[1], STDOUT_FILENO);
		close(pipe_fd_in[0]);
		close(pipe_fd_out[1]);
		close(pipe_fd_in[1]);
		close(pipe_fd_out[0]);
		if (check_red == 1)
			execute_command(cmd, in_out_fd[0], in_out_fd[1]);
		exit (0);
	}
}

void	execute_last_command(char **cmd, int *in_out_fd, int pipe_fd_in[], int check_red)
{
	g_env.pid = fork();
	if (g_env.pid == 0)
	{
		dup2(pipe_fd_in[0], STDIN_FILENO);
		close(pipe_fd_in[1]);
		close(pipe_fd_in[0]);
		if (check_red == 1)
			execute_command(cmd, in_out_fd[0], in_out_fd[1]);
		exit (0);
	}
}

void	pipe_creator(int i, t_pair_pipes *pair_pipes)
{
	if (i % 2 == 0)
	{
		if (pipe(pair_pipes->pipe_fd1) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (pipe(pair_pipes->pipe_fd2) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}
