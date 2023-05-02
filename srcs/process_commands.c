/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:39:04 by victorgiord       #+#    #+#             */
/*   Updated: 2023/05/02 14:56:31 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	pipex(t_parsed_args **cmdrl, t_pair_pipes *p, int i, int *in_out_fd, int check_red)
{
	pipe_creator(i, p);
	if (i == 0)
		execute_first_command(cmdrl[i]->cmd_args, in_out_fd, p->pipe_fd1, check_red);
	else if (i == size_struct(cmdrl) - 1)
	{
		if (i % 2 == 0)
			execute_last_command(cmdrl[i]->cmd_args, in_out_fd, p->pipe_fd2, check_red);
		else if (i % 2 == 1)
			execute_last_command(cmdrl[i]->cmd_args, in_out_fd, p->pipe_fd1, check_red);
	}
	else
	{
		if (i % 2 == 0)
		{
			ex_m_cm(cmdrl[i]->cmd_args, in_out_fd, p->pipe_fd2, p->pipe_fd1, check_red);
			close(p->pipe_fd2[0]);
			close(p->pipe_fd2[1]);
		}
		else if (i % 2 == 1)
		{
			ex_m_cm(cmdrl[i]->cmd_args, in_out_fd, p->pipe_fd1, p->pipe_fd2, check_red);
			close(p->pipe_fd1[0]);
			close(p->pipe_fd1[1]);
		}
	}
}

static void	close_pair_pipes(t_pair_pipes *pair_pipes)
{
	close(pair_pipes->pipe_fd1[0]);
	close(pair_pipes->pipe_fd1[1]);
	close(pair_pipes->pipe_fd2[0]);
	close(pair_pipes->pipe_fd2[1]);
}

static void	wait_all_process(int nbr_cmd, int *status)
{
	int	i;

	i = 0;
	while (i < nbr_cmd)
	{
		waitpid(-1, status, 0);
		if (WIFEXITED(*status))
		{
			g_env.ms_errno = WEXITSTATUS(*status);
		}
		i++;
	}
}

static void	init_in_out(int **in_out_fd)
{
	(*in_out_fd)[0] = STDIN_FILENO;
	(*in_out_fd)[1] = STDOUT_FILENO;
}

int	process_multiple_commands(t_parsed_args **cmd_red_lst)
{
	int				*in_out_fd;
	t_pair_pipes	pair_pipes;
	int				i;
	int				status;
	int				check_red;

	i = 0;
	in_out_fd = malloc(2 * sizeof(int));
	if (in_out_fd == NULL)
		return (-1);
	init_in_out(&in_out_fd);
	while (cmd_red_lst[i])
	{
		check_red = 1;
		if (process_redirection(cmd_red_lst[i]->redirections, &in_out_fd) == -1)
		{
			//printf("Il y a un pb avec la redirection\n");
			check_red = 0;
			
			//free(in_out_fd);
			//free_struct(cmd_red_lst);
		}	
		pipex(cmd_red_lst, &pair_pipes, i, in_out_fd, check_red);

	
		
		i++;
	}
	close_pair_pipes(&pair_pipes);
	wait_all_process(size_struct(cmd_red_lst), &status);
	free(in_out_fd);
	return (1);
}
