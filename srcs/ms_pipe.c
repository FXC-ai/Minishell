/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:35:43 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/29 18:30:32 by vgiordan         ###   ########.fr       */
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
   // int status;

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
        //execution(input_cmd, env);
    }




}

void execute_first_cmd(int pipe_fd[2], char **tab_cmds, char *env[])
{
    pid_t pid;
   // int status;

    pid = fork();
    if (pid == 0)
    {
        //printf("Execution 1st cmd : %s\n", tab_cmds[0]);
        close(pipe_fd[0]);
        dup2(pipe_fd[1],1);
        close(pipe_fd[1]);
        process_redirection(tab_cmds[0], env, 0);
        //redirection();
        //execution(tab_cmds[0], env);
    }    
    else
    {

        //usleep(100);
        //waitpid(pid, &status, 0);
    }
}


void execute_last_cmd(int pipe_fd[2], char **tab_cmds, int nbr_cmds, char *env[])
{
    pid_t pid;
   // int status;

    pid = fork();
    if (pid == 0)
    {
        //printf("Execution last cmd : %s\n", tab_cmds[nbr_cmds-1]);

        close(pipe_fd[1]);
        dup2(pipe_fd[0],0);
        close(pipe_fd[0]);
        process_redirection(tab_cmds[nbr_cmds - 1], env, 0);
        //execution(tab_cmds[nbr_cmds-1], env);
    }
}


void ms_pipe2(char **tab_cmds, char *env[])
{

    int pipe_fd1[2];
    int pipe_fd2[2];

    pid_t pid;

    //char **tab_cmd;

    int nbr_cmds;

    int i;

    nbr_cmds = size_tab(tab_cmds);



    //PROCESSUS 1
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
        //execute_last_cmd(pipe_fd2, tab_cmds, nbr_cmds, env);
        pid = fork();
        if (pid == 0)
        {
            //printf("Execution last cmd : %s\n", tab_cmds[nbr_cmds-1]);

            close(pipe_fd2[1]);
            dup2(pipe_fd2[0],0);
            close(pipe_fd2[0]);
            //execution(tab_cmds[nbr_cmds - 1], env);
            process_redirection(tab_cmds[nbr_cmds-1], env, 0); 
            
            //redirection(tab_cmds[nbr_cmds-1], pipe_fd2, pipe_fd1, env);
        }
        close(pipe_fd2[0]);
        close(pipe_fd2[1]);  
    }
    else if (i % 2 == 0)
    {
        //execute_last_cmd(pipe_fd1, tab_cmds, nbr_cmds, env);
        pid = fork();
        if (pid == 0)
        {
            //printf("Execution last cmd (2) : %s\n", tab_cmds[nbr_cmds-1]);


            close(pipe_fd1[1]);
            dup2(pipe_fd1[0],0);
            close(pipe_fd1[0]);
            //execution(tab_cmds[nbr_cmds - 1], env); 
            process_redirection(tab_cmds[nbr_cmds-1], env, 0); 
            
            //redirection(tab_cmds[nbr_cmds-1], pipe_fd2, pipe_fd1, env);

        }
        close(pipe_fd1[0]);
        close(pipe_fd1[1]);  
    }
    for (i = 0; i < nbr_cmds; i++)
    {
        waitpid(-1, NULL, 0);
    }

    //wait(0);

}