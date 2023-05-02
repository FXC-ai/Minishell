/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:49:47 by fcoindre          #+#    #+#             */
/*   Updated: 2023/05/02 16:03:37 by vgiordan         ###   ########.fr       */
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

void	execute_first_command(char **cmd, int *io, int pipe_fd[], int cr)
{
	g_env.pid = fork();
	if (g_env.pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		if (cr == 1)
			execute_command(cmd, io[0], io[1]);
		exit (0);
	}
}

void	ex_m_cm(char **cmd, int *in_out_fd, t_pair_pipes *pp, int check_red)
{
	g_env.pid = fork();
	if (g_env.pid == 0)
	{
		dup2(pp->pipe_fd1[0], STDIN_FILENO);
		dup2(pp->pipe_fd2[1], STDOUT_FILENO);
		close(pp->pipe_fd1[0]);
		close(pp->pipe_fd2[1]);
		close(pp->pipe_fd1[1]);
		close(pp->pipe_fd2[0]);
		if (check_red == 1)
			execute_command(cmd, in_out_fd[0], in_out_fd[1]);
		exit (0);
	}
}

void	execute_last_command(char **cmd, int *in_out_fd, int p[], int check_red)
{
	g_env.pid = fork();
	if (g_env.pid == 0)
	{
		dup2(p[0], STDIN_FILENO);
		close(p[1]);
		close(p[0]);
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
