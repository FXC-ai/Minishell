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

/*static void display_tab(char **tab, char *name)
{
    int i;

    i = 0;
    printf("Size = %d, Tableau %s :\n", size_tab(tab),name);
    while (tab[i] != NULL)
    {
        printf("  %d: [%s]\n", i, tab[i]);
        i++;
    }
    
}*/

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

        execution(input_cmd, env);
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
        execution(tab_cmds[0], env);
    }    
    else
    {
        wait(0);
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
        execution(tab_cmds[nbr_cmds-1], env);
    }
    else
    {
        wait(0);
    }
}
/*
void	redir (char *cmd, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN); //LA LECTURE DU PROCESS PARENT POINTERA TOUJOURS SUR LE pipfd[0]
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		exec(cmd, env);
	}
}*/

void ms_pipe2_dep(char **tab_cmds, char *env[])
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
            execution(tab_cmds[nbr_cmds-1], env);
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
            execution(tab_cmds[nbr_cmds-1], env);
        }
        close(pipe_fd1[0]);
        close(pipe_fd1[1]);  
    }

    //wait(0);

}


void    printPID(int PID, char *msg, int fd)
{
    ft_putstr_fd("   -> ", fd);
    ft_putstr_fd(msg, fd);
    ft_putnbr_fd(PID, fd);
    ft_putchar_fd('\n', fd);
}

void printPIPE(int pipefd[2], int fd)
{
    ft_putstr_fd("\n", fd);
	ft_putstr_fd("Pipe[0] : lecture = ", fd);
	ft_putnbr_fd(pipefd[0], fd);
	ft_putstr_fd(" | Pipe[1] : ecriture = ", fd);
	ft_putnbr_fd(pipefd[1], fd);
	ft_putstr_fd("\n", fd);

}

void printMSG(char *msg, int index_process,int fd)
{
    ft_putchar_fd('\n', fd);
    ft_putstr_fd(msg, fd);
    ft_putchar_fd(' ', fd);
    ft_putnbr_fd(index_process, fd);
    ft_putchar_fd('\n', fd);

}


void boucle_executor (char *tab_cmd, int (*pipe_fd)[2], int (*former_pipe)[2], char *env[], int fd_debug2)
{
    int pid;

    pipe(*pipe_fd);
    printPIPE(*pipe_fd, fd_debug2);
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
        execution(tab_cmd, env);
    }

}

void ms_pipe2(char **tab_cmds, char *env[])
{

    int pipe_fd[2];
    int former_pipe[2];
    int fd_debug2;
    pid_t pid;

    int process_num;
    int i;

    process_num = size_tab(tab_cmds);

    fd_debug2 = open("debug2.log", O_WRONLY);

    pipe(pipe_fd);
    printPIPE(pipe_fd, fd_debug2);
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
        execution(tab_cmds[0], env);
    }

    i = 0;
    while (i < process_num - 2)
    {
        boucle_executor(tab_cmds[i+1], &pipe_fd, &former_pipe, env, fd_debug2);
        i++;
    }

    pid = fork();
    if (pid)
    {        
        waitpid(pid, NULL, 0);
    }
    else
    {
        execution(tab_cmds[process_num-1], env);
    }

    while(process_num > 0)
    {
        wait(NULL);
        process_num--;
    }

    close(fd_debug2);
}
/*
void ms_pipe2(char **tab_cmds, char *env[])
{




     
}
*/

/*
int main (int argc, char *argv[], char *env[])
{
    
    char *tab_cmd_test1[6];

    tab_cmd_test1[0] = "ls";
    tab_cmd_test1[1] = "grep a";
    tab_cmd_test1[2] = "grep t";
    tab_cmd_test1[3] = "wc";
    tab_cmd_test1[4] = "cat -e";
    tab_cmd_test1[5] = NULL;

    ms_pipe2(tab_cmd_test1, env);
    
    
    
    
    
    char *tab_cmd_test2[4];

    tab_cmd_test2[0] = "cat debug.log";
    tab_cmd_test2[1] = "grep a";
    tab_cmd_test2[2] = "wc";
    tab_cmd_test2[3] = NULL;

    ms_pipe2(tab_cmd_test2, env);
    

    

    
    char *tab_cmd_test3[3];

    tab_cmd_test3[0] = "ls";
    tab_cmd_test3[1] = "grep a";
    tab_cmd_test3[2] = NULL;

    ms_pipe2(tab_cmd_test3, env);
    
    

    
    return 0;
}*/


    //printPIPE(pipe_fd, fd_debug2);
    /* 
    La valeur du pid est :
        - 0 pour le processus fils
        - >0 pour le processis parent
    
    */

    //pipefd[0] : est le bout de lecture !!!!!!
    //pipefd[1] : est le bout d'ecriture !!!!!!
