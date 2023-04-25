/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:28:13 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/25 16:16:28 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	executor(t_parsed_args **cmd_red_lst, int **in_out_fd, int wth_ext)
{
	execute_command(cmd_red_lst[0]->cmd_args, (*in_out_fd)[0], (*in_out_fd)[1]);
	if ((*in_out_fd)[0] != STDIN_FILENO)
	{
		close((*in_out_fd)[0]);
	}
	if ((*in_out_fd)[1] != STDOUT_FILENO)
	{
		close((*in_out_fd)[1]);
	}
	if (wth_ext == 1)
	{
		exit(SUCCESS);
	}
}

int	process_single_command(t_parsed_args **cmd_red_lst, int *in_out_fd)
{
	int		r;
	int		status;
	pid_t	pid;

	r = is_builtins(cmd_red_lst[0]->cmd_args[0]);
	if (process_redirection(cmd_red_lst[0]->redirections, &in_out_fd) == -1)
	{
		free(in_out_fd);
		free_struct(cmd_red_lst);
		return (-1);
	}
	if (r == 2 || r == 4 || r == BUILTIN_UNSET || r == BUILTIN_EXIT)
		executor(cmd_red_lst, &in_out_fd, 0);
	else
	{
		pid = fork();
		if (pid == 0)
			executor(cmd_red_lst, &in_out_fd, 1);
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_env.ms_errno = WEXITSTATUS(status);
		}
	}
	return (1);
}
