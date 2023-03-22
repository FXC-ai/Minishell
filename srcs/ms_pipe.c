/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoindre <fcoindre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 18:32:05 by fcoindre          #+#    #+#             */
/*   Updated: 2023/03/22 18:35:15 by fcoindre         ###   ########.fr       */
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
        printf("dfdf\n");
        i++;
    }
    
}

int find_ind_filename(char **tab_cmd_path)
{
    int i;
    char *file_name;

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
    int in_fd;

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
            //printf("tab_cmd[%d] = %s\n", i, tab_cmd[i]);
            //display_tab(tab_cmd_path, "tab_cmd_path");

            if (strrchr(tab_cmd[i], '>') != NULL)
            {

                ind_file_name = find_ind_filename(tab_cmd_path);
                out_fd = open(tab_cmd_path[ind_file_name], 
                                O_WRONLY | O_CREAT | O_TRUNC,
                                 0644);

                /*printf("Redirect to : %s (fd = %d).\n\n", 
                        tab_cmd_path[ind_file_name],
                        out_fd);*/

                delete_from_chevron(tab_cmd_path);
                
                display_tab(tab_cmd_path, "tab_cmd_path");
                
                dup2(out_fd,1);



 
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




int main (int argc, char *argv[], char *env[])
{

    char *tab_cmd[3];

    tab_cmd[0] = "ls -la";
    tab_cmd[1] = "wc > file";
    tab_cmd[2] = NULL;

    //display_tab(tab_cmd, "tab_cmd");

    //delete_from_i(tab_cmd, 2);


    //display_tab(tab_cmd, "tab_cmd");

    ms_pipe(tab_cmd, env);


    return 0;
}
