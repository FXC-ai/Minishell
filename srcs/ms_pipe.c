/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:35:43 by vgiordan          #+#    #+#             */
/*   Updated: 2023/04/07 16:33:16 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"


typedef struct s_cmd_to_execute {

	int index;
	int fd_in;
	int fd_out;
	int pipe_fd1[2];
	int pipe_fd2[2];
	char *cmd;

} t_cmd_to_execute;

static void	error_exit(int code_error)
{
	perror("minishell");
	exit(code_error);
}


void execution (char *input_cmd, char *env[])
{
	char **tab_cmd;
 
	tab_cmd = ft_split_lexer(input_cmd, ' ');

	if (execve(normalize_cmd(tab_cmd[0], env), tab_cmd, env) == -1)
	{
		freemalloc(tab_cmd, size_tab(tab_cmd));
		error_exit(EXIT_FAILURE);
	}
}


void redirection (char *input_cmd, int previous_pipe[2], int next_pipe[2], char *env[])
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		close(previous_pipe[1]);
		close(next_pipe[0]);

		dup2(previous_pipe[0],0);
		dup2(next_pipe[1],1);

		close(previous_pipe[0]);
		close(next_pipe[1]);       

		process_redirection(input_cmd, env, 0);
	}
}

void execute_first_cmd(int pipe_fd[2], char **tab_cmds, char *env[])
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1],1);
		close(pipe_fd[1]);
		process_redirection(tab_cmds[0], env, 0);
	}    

}
/*
void execute_first_cmd(t_cmd_to_execute cmd_to_execute, char *env[])
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1],1);
		close(pipe_fd[1]);
		process_redirection(tab_cmds[0], env, 0);
	}    

}*/



void ms_pipe2(char **tab_cmds, int nbr_cmds, char *env[])
{

	int pipe_fd1[2];
	int pipe_fd2[2];
	int status;
	int i;
	/*
	t_cmd_to_execute cmd_to_execute;

	cmd_to_execute.index = 0;
	cmd_to_execute.fd_in = -1;
	cmd_to_execute.fd_out = -1;
	cmd_to_execute.
	cmd_to_execute.cmd = tab_cmds[0];
	*/

	pipe(pipe_fd1);

	execute_first_cmd(pipe_fd1, tab_cmds, env);
	i = 0;
	while (i < nbr_cmds - 2)
	{
		if (i % 2 == 0)
		{

			pipe(pipe_fd2);
			redirection(tab_cmds[i + 1], pipe_fd1, pipe_fd2, env);

			close(pipe_fd1[0]);
			close(pipe_fd1[1]);          
		}
		else if (i % 2 == 1)
		{

			pipe(pipe_fd1);
			redirection(tab_cmds[i + 1], pipe_fd2, pipe_fd1, env);

			close(pipe_fd2[0]);
			close(pipe_fd2[1]);
		}
		i++;
	}
	
	if (i % 2 == 1)
	{
		global_sig.pid = fork();
		if (global_sig.pid == 0)
		{
			close(pipe_fd2[1]);
			dup2(pipe_fd2[0],0);
			close(pipe_fd2[0]);
			process_redirection(tab_cmds[nbr_cmds-1], env, 0);
		}
		close(pipe_fd2[1]);
		close(pipe_fd2[0]);
	}
	else if (i % 2 == 0)
	{
		global_sig.pid = fork();
		if (global_sig.pid == 0)
		{
			close(pipe_fd1[1]);
			dup2(pipe_fd1[0],0);
			close(pipe_fd1[0]);
			process_redirection(tab_cmds[nbr_cmds-1], env, 0);
		}
		close(pipe_fd1[0]);
		close(pipe_fd1[1]);  
	}

	for (i = 0; i < nbr_cmds; i++)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
        {
            global_sig.ms_errno = WEXITSTATUS(status);
        }
	}

}