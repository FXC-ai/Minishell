/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:32:05 by fcoindre          #+#    #+#             */
/*   Updated: 2023/03/23 16:21:47 by fcoindre         ###   ########.fr       */
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
/*
static int exist_redirection(char *cmd)
{
    return (ft_strchr(cmd, '>') != NULL || ft_strchr(cmd, '<') != NULL);
}
*/
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
/*
static void redirection (char **)
{




}

*/
static void display_tab(char **tab, char *name)
{
    int i;

    i = 0;
    printf("Size = %d, Tableau %s :\n", size_tab(tab),name);
    while (tab[i] != NULL)
    {
        printf("  %d: [%s]\n", i, tab[i]);
        i++;
    }
    
}

int find_ind_filename(char **tab_cmd_path)
{
    int i;


    i = 0;
    while (tab_cmd_path[i] != NULL)
    {
        if (strrchr(tab_cmd_path[i], '>') != NULL)
        {
            return (i + 1);
        }
        i++;
    }
    
    return (-1);
}
/*
void delete_from_chevron(char **tab_cmd_path)
{

    int i;
    char *file_name;
    int size_tab_cmd_path;


    i = 0;
    while (tab_cmd_path[i] != NULL)
    {
        if (strrchr(tab_cmd_path[i], '>') != NULL)
        {
            break;
        }
        i++;
    }
    
    while (tab_cmd_path[i] != NULL)
    {
        tab_cmd_path[i] = NULL;
        i++;
    }

        //printf("df\n");
}

*/
/*
char **duplicate_tab(char **tab, int i)
{
    int size;

    size = 



}
*/

void ms_pipe(char *tab_cmd[2], char *env[]) 
{
    int pid;
    int i;
    int pipefd[2];
    char **tab_cmd_path;

    int out_fd;
    //int in_fd;

    int ind_file_name;

    //pipefd[0] : est le bout de lecture !!!!!!
    //pipefd[1] : est le bout d'ecriture !!!!!!


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
            
            tab_cmd_path = ft_split_lexer(tab_cmd[i], ' ');         


            if (strrchr(tab_cmd[i], '>') != NULL)
            {

                ind_file_name = find_ind_filename(tab_cmd_path);
                out_fd = open(tab_cmd_path[ind_file_name], 
                                O_WRONLY | O_CREAT | O_TRUNC,
                                 0644);
                
                dup2(out_fd,1);

                if (i == 1)
                {
                    dup2(pipefd[0],0);

                }

                if (execve(normalize_cmd(tab_cmd_path[0], env), tab_cmd_path, env) == -1)
                {
                    freemalloc(tab_cmd_path, size_tab(tab_cmd_path));
                    error_exit(EXIT_FAILURE);
                }

                //exit(0);
            }
            else if (strrchr(tab_cmd[i], '<') != NULL)
            {
                printf("OK ba la ya redirection dans l'autre sens <\n\n");

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

                if (execve(normalize_cmd(tab_cmd_path[0], env), tab_cmd_path, env) == -1)

                
                tab_cmd_path = ft_split(tab_cmd[i], ' ');
                
                if (execve(cmd_exists(tab_cmd_path[0], env), tab_cmd_path, env) == -1)
                {
                    freemalloc(tab_cmd_path, size_tab(tab_cmd_path));
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



/*
void ms_pipe2(char **tab_cmds, char *env[])
{

    int nbr_fct;
    int i;
    char *cmd;
    char **tab_cmd;
    int pipe_fd[2];
    int pid;

    nbr_fct = size_tab(tab_cmds);

    i = 0;
    while (i < nbr_fct)
    {
        
        cmd = tab_cmds[i];
        tab_cmd = ft_split_lexer(tab_cmds[i], ' ');
        display_tab(tab_cmd, "tab_cmd");

        if (i == 0)
        {
            pipe(pipe_fd);
            close(pipe_fd[0]);

            dup2(pipe_fd[1], 1);

            pid = fork();
            if (pid == 0)
            {
                printf("Je suis l'enfant je fonctionne");
                if (execve(normalize_cmd(tab_cmd[0], env), tab_cmd, env) == -1)
                {
                    freemalloc(tab_cmd, size_tab(tab_cmd));
                    error_exit(EXIT_FAILURE);
                }

            }
        }

        
        wait(0);

        i++;

    }
    




}

*/





void ms_pipe2(char **tab_cmds, char *env[])
{

    //int tab[2];
    //int i;
    /*char *cmd;
    char **tab_cmd;
    int pipe_fd[2];
    int pid;*/
    //int nbr_fct = ;

    // char *test[2];
    // test[0] = "ls";
    // test[1] = NULL;
    // execve("/bin/ls", test, env);

    

    
    int pipe_fd1[2];
    int pipe_fd2[2];
    int pipe_fd3[2];

    pid_t pid;


    char **tab_cmd;

    pipe(pipe_fd1);
    pipe(pipe_fd2);
    pipe(pipe_fd3);

    //PROCESSUS 1
    pid = fork();
    if (pid == 0)
    {
        tab_cmd = ft_split(tab_cmds[0], ' ');
        display_tab(tab_cmd, "tab_cmd");

        close(pipe_fd2[0]);
        close(pipe_fd2[1]);
        close(pipe_fd3[0]);
        close(pipe_fd3[1]);

        close(pipe_fd1[0]);
        dup2(pipe_fd1[1],1);
        close(pipe_fd1[1]);

        
        if (execve(normalize_cmd(tab_cmd[0], env), tab_cmd, env) == -1)
        {
            freemalloc(tab_cmd, size_tab(tab_cmd));
            error_exit(EXIT_FAILURE);
        }
    }

    //PROCESSUS 2
    pid = fork();
    if (pid == 0)
    {
        tab_cmd = ft_split(tab_cmds[1], ' ');
        display_tab(tab_cmd, "tab_cmd");

        close(pipe_fd3[0]);
        close(pipe_fd3[1]);

        close(pipe_fd1[1]);
        close(pipe_fd2[0]);

        dup2(pipe_fd1[0],0);
        dup2(pipe_fd2[1],1);

        close(pipe_fd1[0]);
        close(pipe_fd2[1]);       



        if (execve(normalize_cmd(tab_cmd[0], env), tab_cmd, env) == -1)
        {
            freemalloc(tab_cmd, size_tab(tab_cmd));
            error_exit(EXIT_FAILURE);
        }
    }  
    
    //pipefd[0] : est le bout de lecture !!!!!!
    //pipefd[1] : est le bout d'ecriture !!!!!!

    //PROCESSUS 3
    pid = fork();
    if (pid == 0)
    {
        tab_cmd = ft_split(tab_cmds[2], ' ');
        display_tab(tab_cmd, "tab_cmd");

        close(pipe_fd1[0]);
        close(pipe_fd1[1]);

        close(pipe_fd2[1]);
        close(pipe_fd3[0]);

        dup2(pipe_fd2[0],0);
        dup2(pipe_fd3[1],1);

        close(pipe_fd2[0]);
        close(pipe_fd3[1]);

        if (execve(normalize_cmd(tab_cmd[0], env), tab_cmd, env) == -1)
        {
            freemalloc(tab_cmd, size_tab(tab_cmd));
            error_exit(EXIT_FAILURE);
        }

    }


    //PROCESSUS 4
    pid = fork();
    if (pid == 0)
    {
        tab_cmd = ft_split(tab_cmds[3], ' ');
        display_tab(tab_cmd, "tab_cmd");

        close(pipe_fd1[0]);
        close(pipe_fd1[1]);

        close(pipe_fd2[0]);
        close(pipe_fd2[1]);

        close(pipe_fd3[1]);

        dup2(pipe_fd3[0],0);

        close(pipe_fd3[0]);


        if (execve(normalize_cmd(tab_cmd[0], env), tab_cmd, env) == -1)
        {
            freemalloc(tab_cmd, size_tab(tab_cmd));
            error_exit(EXIT_FAILURE);
        }

    }

    wait(0);
    //wait(0);
    close(pipe_fd1[0]);
    close(pipe_fd1[1]);

    close(pipe_fd2[0]);
    close(pipe_fd2[1]);  

    close(pipe_fd3[0]);
    close(pipe_fd3[1]);  
    
    //printf("nbr_func = %d, sizeof = %zu",nbr_fct, sizeof(*tab_pipe));


}

int main (int argc, char *argv[], char *env[])
{

    char *tab_cmd_test1[5];

    tab_cmd_test1[0] = "ls -la";
    tab_cmd_test1[1] = "grep utils";
    tab_cmd_test1[2] = "wc -l";
    tab_cmd_test1[3] = "cat -e";
    tab_cmd_test1[4] = NULL;

    ms_pipe2(tab_cmd_test1, env);

    //int *(tab[2])[3];

    




    return 0;
}

    /*
    char *tab_cmd_test2[4];

    tab_cmd_test2[0] = "ls";
    tab_cmd_test2[1] = "grep a > myfile";
    tab_cmd_test2[2] = "wc";
    tab_cmd_test2[3] = NULL;

    char *tab_cmd_test3[4];

    tab_cmd_test2[0] = "ls > myfile";
    tab_cmd_test2[1] = "wc -w";
    tab_cmd_test2[2] = "wc";
    tab_cmd_test2[3] = NULL;
    */