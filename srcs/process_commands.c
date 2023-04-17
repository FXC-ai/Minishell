/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 23:39:04 by victorgiord       #+#    #+#             */
/*   Updated: 2023/04/16 23:31:57 by victorgiord      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void execute_parent_process(int *in_out_fd, int *status)
{
    waitpid(global_sig.pid, status, 0);
    if (WIFEXITED(*status))
    {
        global_sig.ms_errno = WEXITSTATUS(*status);
    }
    if (in_out_fd[1] != STDIN_FILENO && in_out_fd[1] != STDOUT_FILENO)
    {
        close(in_out_fd[1]); // close write end of pipe
    }
    ft_putstr_fd("End pid\n", 2);
}



void close_pipes(int *pipe_fd)
{
    if (pipe_fd[0] != STDIN_FILENO) close(pipe_fd[0]);
    if (pipe_fd[1] != STDOUT_FILENO) close(pipe_fd[1]);
}

void redirect_pipe_fds(int *in_out_fd, int *pipe_fd, int cmd_index)
{
    if (cmd_index > 0) in_out_fd[0] = pipe_fd[0];
    if (pipe_fd[1] != STDOUT_FILENO) in_out_fd[1] = pipe_fd[1];
}

int process_multiple_commands(t_parsed_args **cmd_red_lst, char *env[])
{
    int *in_out_fd;
    int pipe_fd[2];
    int status;
    int i = 0;

    in_out_fd = malloc(2 * sizeof(int));
    in_out_fd[0] = STDIN_FILENO;
    in_out_fd[1] = STDOUT_FILENO;
	(void) pipe_fd;
    while (cmd_red_lst[i])
    {
		printf("I = %d\n", i);
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
        if (process_redirection(cmd_red_lst[i]->redirections, &in_out_fd, env) == -1)
        {
            free(in_out_fd);
            free_struct(cmd_red_lst);
        }
		else
		{
			global_sig.pid = fork();
			if (global_sig.pid == 0)
			{
				close(pipe_fd[0]);
                close(in_out_fd[1]);
                execute_command(cmd_red_lst[i]->cmd_args, in_out_fd[0], pipe_fd[1], env);
                close(pipe_fd[1]);
                close(in_out_fd[0]);
                exit(EXIT_SUCCESS);
			}
			else
			{
				close(pipe_fd[1]);
                close(in_out_fd[0]);
                in_out_fd[0] = pipe_fd[0];
                execute_parent_process(in_out_fd, &status);
                close(pipe_fd[0]);
				if (in_out_fd[1] != STDOUT_FILENO)
                	close(in_out_fd[1]);
			}
		
		}
		i++;
	}
    free(in_out_fd);
	return (1);
}

int	process_single_command(t_parsed_args **cmd_red_lst, int *in_out_fd, char *env[])
{
	int	r;
	int	status;

	r = is_builtins(cmd_red_lst[0]->cmd_args[0]);
	if (process_redirection(cmd_red_lst[0]->redirections, &in_out_fd, env) == -1)
	{
		free(in_out_fd);
		free_struct(cmd_red_lst);
		return (-1);
	}
	if (r == BUILTIN_CD || r == BUILTIN_EXPORT || r == BUILTIN_UNSET || r == BUILTIN_EXIT)
	{
		execute_command(cmd_red_lst[0]->cmd_args, in_out_fd[0], in_out_fd[1], env);
		if (in_out_fd[0] != STDIN_FILENO)
		{
			close(in_out_fd[0]);
		}
		if (in_out_fd[1] != STDOUT_FILENO)
		{
			close(in_out_fd[1]);
		}
	}
	else
	{
		global_sig.pid = fork();
		if (global_sig.pid == 0)
		{
			execute_command(cmd_red_lst[0]->cmd_args, in_out_fd[0], in_out_fd[1], env);
			if (in_out_fd[0] != STDIN_FILENO)
			{
				close(in_out_fd[0]);
			}
			if (in_out_fd[1] != STDOUT_FILENO)
			{
				close(in_out_fd[1]);
			}
			exit(SUCCESS);
		}
		else
		{
			waitpid(global_sig.pid, &status, 0);
			if (WIFEXITED(status))
			{
				global_sig.ms_errno = WEXITSTATUS(status);
			}
			
		}
	}
	return (1);
}
