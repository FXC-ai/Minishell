/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:39:04 by victorgiord       #+#    #+#             */
/*   Updated: 2023/04/21 12:14:26 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	execute_parent_process(int *in_out_fd, int *status)
{
	waitpid(g_env.pid, status, 0);
	if (WIFEXITED(*status))
	{
		g_env.ms_errno = WEXITSTATUS(*status);
	}
	(void) in_out_fd;
	ft_putstr_fd("End pid\n", 2);
}

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

void	execute_first_command(char **cmd, int *in_out_fd, int pipe_fd[])
{
	g_env.pid = fork();
	if (g_env.pid == 0)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execute_command(cmd, in_out_fd[0], in_out_fd[1]);
		exit (0);
	}
}

void	execute_middle_command(char **cmd, int *in_out_fd, int pipe_fd_in[], int pipe_fd_out[])
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
		execute_command(cmd, in_out_fd[0], in_out_fd[1]);
		exit (0);
	}
}

void	execute_last_command(char **cmd, int *in_out_fd, int pipe_fd_in[])
{
	g_env.pid = fork();
	if (g_env.pid == 0)
	{
		dup2(pipe_fd_in[0], STDIN_FILENO);
		close(pipe_fd_in[1]);
		close(pipe_fd_in[0]);
		execute_command(cmd, in_out_fd[0], in_out_fd[1]);
		exit (0);
	}
}

static void pipe_creator(int i, t_pair_pipes *pair_pipes)
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

static void close_pair_pipes(t_pair_pipes *pair_pipes)
{
	close(pair_pipes->pipe_fd1[0]);
	close(pair_pipes->pipe_fd1[1]);
	close(pair_pipes->pipe_fd2[0]);
	close(pair_pipes->pipe_fd2[1]);
}

int	process_multiple_commands(t_parsed_args **cmd_red_lst)
{
	int	*in_out_fd;
	t_pair_pipes pair_pipes;
	int	i = 0;
	int	nbr_cmd;
	int	status;

	nbr_cmd = size_struct(cmd_red_lst);
	in_out_fd = malloc(2 * sizeof(int));
	if (in_out_fd == NULL)
		return (-1);
	in_out_fd[0] = STDIN_FILENO;
	in_out_fd[1] = STDOUT_FILENO;
	while (cmd_red_lst[i])
	{
		if (process_redirection(cmd_red_lst[i]->redirections, &in_out_fd) == -1)
		{
			free(in_out_fd);
			free_struct(cmd_red_lst);
		}
		else
		{
			pipe_creator(i, &pair_pipes);
			if (i == 0)
			{
				execute_first_command(cmd_red_lst[i]->cmd_args, in_out_fd, pair_pipes.pipe_fd1);
			}
			else if (i == nbr_cmd - 1)
			{
				if (i % 2 == 0)
					execute_last_command(cmd_red_lst[i]->cmd_args, in_out_fd, pair_pipes.pipe_fd2);
				else if (i % 2 == 1)
					execute_last_command(cmd_red_lst[i]->cmd_args, in_out_fd, pair_pipes.pipe_fd1);
			}
			else
			{
				if (i % 2 == 0)
				{
					execute_middle_command(cmd_red_lst[i]->cmd_args, in_out_fd, pair_pipes.pipe_fd2, pair_pipes.pipe_fd1);
					close(pair_pipes.pipe_fd2[0]);
					close(pair_pipes.pipe_fd2[1]);
				}
				else if (i % 2 == 1)
				{
					execute_middle_command(cmd_red_lst[i]->cmd_args, in_out_fd, pair_pipes.pipe_fd1, pair_pipes.pipe_fd2);
					close(pair_pipes.pipe_fd1[0]);
					close(pair_pipes.pipe_fd1[1]);
				}
			}
		}
		i++;
	}
	close_pair_pipes(&pair_pipes);
	/*close(pair_pipes.pipe_fd1[0]);
	close(pair_pipes.pipe_fd1[1]);
	close(pair_pipes.pipe_fd2[0]);
	close(pair_pipes.pipe_fd2[1]);*/
	i = 0;
	while (i < nbr_cmd)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			g_env.ms_errno = WEXITSTATUS(status);
		}
		i++;
	}
	free(in_out_fd);
	return (1);
}


static void executor (t_parsed_args **cmd_red_lst, int *in_out_fd, int with_exit)
{
		execute_command(cmd_red_lst[0]->cmd_args, in_out_fd[0], in_out_fd[1]);
		if (in_out_fd[0] != STDIN_FILENO)
		{
			close(in_out_fd[0]);
		}
		if (in_out_fd[1] != STDOUT_FILENO)
		{
			close(in_out_fd[1]);
		}
		if (with_exit == 1)
		{
			exit(SUCCESS);			
		}
}


int	process_single_command(t_parsed_args **cmd_red_lst, int *in_out_fd)
{
	int	r;
	int	status;

	r = is_builtins(cmd_red_lst[0]->cmd_args[0]);
	if (process_redirection(cmd_red_lst[0]->redirections, &in_out_fd) == -1)
	{
		free(in_out_fd);
		free_struct(cmd_red_lst);
		return (-1);
	}
	if (r == BUILTIN_CD || r == BUILTIN_EXPORT || r == BUILTIN_UNSET || r == BUILTIN_EXIT)
		executor(cmd_red_lst, in_out_fd, 0);
	else
	{
		g_env.pid = fork();
		if (g_env.pid == 0)
			executor(cmd_red_lst, in_out_fd, 1);
		else
		{
			waitpid(g_env.pid, &status, 0);
			if (WIFEXITED(status))
				g_env.ms_errno = WEXITSTATUS(status);
		}
	}
	return (1);
}
