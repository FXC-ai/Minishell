/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:39:04 by victorgiord       #+#    #+#             */
/*   Updated: 2023/05/02 15:59:21 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	pipex1(t_parsed_args **cmd, t_pair_pipes *p, int *io, t_i_check *ic)
{
	if (ic->i % 2 == 0)
	{
		execute_last_command(cmd[ic->i]->cmd_args, \
			io, p->pipe_fd2, ic->check_red);
	}
	else if (ic->i % 2 == 1)
	{
		execute_last_command(cmd[ic->i]->cmd_args, \
			io, p->pipe_fd1, ic->check_red);
	}
}

static void	pipex2(t_parsed_args **cmd, t_pair_pipes *p, int *io, t_i_check *ic)
{
	t_pair_pipes	*pp;

	pp = malloc(sizeof(t_pair_pipes));
	if (ic->i % 2 == 0)
	{
		pp->pipe_fd1[0] = p->pipe_fd2[0];
		pp->pipe_fd1[1] = p->pipe_fd2[1];
		pp->pipe_fd2[0] = p->pipe_fd1[0];
		pp->pipe_fd2[1] = p->pipe_fd1[1];
		ex_m_cm(cmd[ic->i]->cmd_args, io, pp, ic->check_red);
		free(pp);
		close(p->pipe_fd2[0]);
		close(p->pipe_fd2[1]);
	}
	else if (ic->i % 2 == 1)
	{
		pp->pipe_fd1[0] = p->pipe_fd1[0];
		pp->pipe_fd1[1] = p->pipe_fd1[1];
		pp->pipe_fd2[0] = p->pipe_fd2[0];
		pp->pipe_fd2[1] = p->pipe_fd2[1];
		ex_m_cm(cmd[ic->i]->cmd_args, io, pp, ic->check_red);
		free(pp);
		close(p->pipe_fd1[0]);
		close(p->pipe_fd1[1]);
	}
}

static void	pipex(t_parsed_args **cmd, t_pair_pipes *p, int *io, t_i_check *ic)
{
	pipe_creator(ic->i, p);
	if (ic->i == 0)
	{
		execute_first_command(cmd[ic->i]->cmd_args, \
			io, p->pipe_fd1, ic->check_red);
	}
	else if (ic->i == size_struct(cmd) - 1)
	{
		pipex1(cmd, p, io, ic);
	}
	else
	{
		pipex2(cmd, p, io, ic);
	}
}

static void	close_pair_pipes(t_pair_pipes *pair_pipes)
{
	close(pair_pipes->pipe_fd1[0]);
	close(pair_pipes->pipe_fd1[1]);
	close(pair_pipes->pipe_fd2[0]);
	close(pair_pipes->pipe_fd2[1]);
}

int	process_multiple_commands(t_parsed_args **cmd_red_lst)
{
	int				*in_out_fd;
	t_pair_pipes	pair_pipes;
	int				status;
	t_i_check		i_check_red;

	i_check_red.i = 0;
	in_out_fd = malloc(2 * sizeof(int));
	if (in_out_fd == NULL)
		return (-1);
	init_in_out(&in_out_fd);
	while (cmd_red_lst[i_check_red.i])
	{
		i_check_red.check_red = 1;
		if (process_redirection(cmd_red_lst[i_check_red.i]->redirections, \
			&in_out_fd) == -1)
			i_check_red.check_red = 0;
		pipex(cmd_red_lst, &pair_pipes, in_out_fd, &i_check_red);
		i_check_red.i++;
	}
	close_pair_pipes(&pair_pipes);
	wait_all_process(size_struct(cmd_red_lst), &status);
	free(in_out_fd);
	return (1);
}
