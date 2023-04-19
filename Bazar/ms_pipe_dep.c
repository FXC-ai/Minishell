/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_dep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:32:05 by fcoindre          #+#    #+#             */
/*   Updated: 2023/04/19 17:42:10 by fcoindre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"


static void	error_exit(int code_error)
{
	perror("minishell");
	exit(code_error);
}

static void	freemalloc(char **result, int j)
{
	while (j >= 0)
	{
		free(result[j]);
		result[j] = NULL;
		j--;
	}
	free(result);
}

void execution (char *input_cmd)
{
    char **tab_cmd;
 
    tab_cmd = ft_split_lexer(input_cmd, ' ');

    if (execve(normalize_cmd(tab_cmd[0]), tab_cmd) == -1)
    {
        freemalloc(tab_cmd, size_tab(tab_cmd));
        error_exit(EXIT_FAILURE);
    }
}

void boucle_executor (char *tab_cmd, int (*pipe_fd)[2], int (*former_pipe)[2])
{

    int pid;

    pipe(*pipe_fd);
    pid = fork();
    if (pid)
    {
        (*pipe_fd)[0] = (*former_pipe)[1];
        (*former_pipe)[0] = (*pipe_fd)[0];
        (*former_pipe)[1] = (*pipe_fd)[1];
        close((*pipe_fd)[1]);
        dup2((*pipe_fd)[0], 0);
        //waitpid(pid, NULL, 0);
    }
    else
    {
        close((*pipe_fd)[0]);
        dup2((*pipe_fd)[1], 1);
        execution(tab_cmd);
    }

}

void ms_pipe2(char **tab_cmds)
{
    int pipe_fd[2];
    int former_pipe[2];

    pid_t pid;

    int process_num;
    int i;

    process_num = size_tab(tab_cmds);

    pipe(pipe_fd);
    pid = fork();
    if (pid)
    {
        former_pipe[0] = pipe_fd[0];
        former_pipe[1] = pipe_fd[1];
        close(pipe_fd[1]);
        dup2(pipe_fd[0], 0);
        //waitpid(pid, NULL, 0);
    }
    else
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], 1);
        execution(tab_cmds[0]);
    }

    i = 0;
    while (i < process_num - 2)
    {
        boucle_executor(tab_cmds[i+1], &pipe_fd, &former_pipe);
        i++;
    }

    pid = fork();
    if (pid)
    {        
        //waitpid(pid, NULL, 0);
    }
    else
    {
        execution(tab_cmds[process_num-1]);
    }
    
    /*while(process_num > 0)
    {
        wait(NULL);
        process_num--;
    }*/

}

