/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:25:50 by vgiordan          #+#    #+#             */
/*   Updated: 2023/03/22 12:26:32 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

/*static int reverse_bit(int i)
{
    return (!(i));
}*/

static void	error_exit(int code_error)
{
	perror("minishell");
	exit(code_error);
}

static int exist_redirection(char *cmd)
{
    return (ft_strchr(cmd, '>') != NULL || ft_strchr(cmd, '<') != NULL);
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

static int size_tab(char **tab)
{
    int i;

    i = 0;
    while(tab[i] != NULL)
        i++;
    return (i);
}

void ms_pipe(char *tab_cmd[2], char *env[]) 
{
    int pid;
    int i;
    int pipefd[2];
    int pipe_status;
    char **cmd;

    pipe_status = pipe(pipefd);
    if (pipe(pipefd) == -1)
    {
        error_exit(EXIT_FAILURE);
    }
    
    i = 0;
    while (i < 2)
    {
        pid = fork();

        if (pid < 0)
        {
            error_exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            close(pipefd[i]);
            if (exist_redirection(tab_cmd[i]))
            {
                process_redirection(tab_cmd[i]);
                //exit(0);
            }
            else
            {
                if (i == 0)
                {
                    dup2(pipefd[1],1);
                }
                else
                {
                    dup2(pipefd[0],0);
                }
                
                cmd = ft_split(tab_cmd[i], ' ');
                
                if (execve(cmd_exists(cmd[0], env), cmd, env) == -1)
                {
                    freemalloc(cmd, size_tab(cmd));
                    error_exit(EXIT_FAILURE);
                }
                    
            }
            exit(0);
        }
        
        i++;
    }
    
    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    //printf("Tous les processus enfants sont terminés.\n");
}