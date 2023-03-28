
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


int **matrix_creator(int process_num)
{
    int len;
	int *ptr;
    int **arr;
    int i;

	len = sizeof(int *) * process_num + sizeof(int) * 2 * process_num;
	arr = (int **)malloc(len);
	ptr = (int *)(arr + process_num);

    i = 0;
    while(i < process_num)
    {
        arr[i] = (ptr + 2 * i);
        i++;
    }

	return arr;
}

void printMSG(char *msg, int index_process)
{

    int fd = open("debug2.log", O_WRONLY | O_APPEND);

    ft_putchar_fd('\n', fd);
    ft_putstr_fd(msg, fd);
    ft_putchar_fd(' ', fd);
    ft_putnbr_fd(index_process, fd);
    ft_putchar_fd('\n', fd);


    close(fd);

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



int ms_pipe3(int process_num, char **tab_cmds, char *env[]) 
{

    int pids[process_num];

    int **pipes = matrix_creator(process_num +1);

    int i;
    for (i = 0; i < process_num + 1; i++) 
    {
        if (pipe(pipes[i]) == -1) {
            //printMSG("Erro with creating pipe", i);
            printf("Error with creating pipe\n");
            return 1;
        }
    }

    for (i = 0; i < process_num; i++) 
    {
        pids[i] = fork();
        if (pids[i] == -1) 
        {
            //printMSG("Erro with creating process", i);
            printf("Error with creating process\n");
            return 2;
        }

        if (pids[i] == 0) 
        {
            // Child process
            int j;
            for (j = 0; j < process_num + 1; j++) 
            {
                if (i != j) 
                {
                    close(pipes[j][0]);
                }
                if (i + 1 != j) 
                {
                    close(pipes[j][1]);
                }
            }


            // dup2(pipes[i][0],0);
            // dup2(pipes[i+1][1],1);

            // printMSG(tab_cmds[i], i);

            // execution(tab_cmds[i], env);
            int x;
            if (read(pipes[i][0], &x, sizeof(int)) == -1) 
            {
                printf("Error at reading\n");
                return 3;
            }

            printf("(%d) Got %d\n", i, x);
            printMSG("x = ", x);
            x++;
            if (write(pipes[i + 1][1], &x, sizeof(int)) == -1) {
                printf("Error at writing\n");
                return 4;
            }
            printf("(%d) Sent %d\n", i, x);
            close(pipes[i][0]);
            close(pipes[i + 1][1]);
            return 0;
        }

    }

    // Main process
    int j;
    for (j = 0; j < process_num + 1; j++) 
    {
        if (j != process_num) {
            close(pipes[j][0]);
        }
        if (j != 0) {
            close(pipes[j][1]);
        }
    }


    // dup2(pipes[0][0], 0);
    // dup2(pipes[0][1], 1);
    

    // execution(tab_cmds[0]);

    int y = 5;
    printf("Main process sent %d\n", y);
    if (write(pipes[0][1], &y, sizeof(int)) == -1) 
    {
        printf("Error at writing\n");
        return 4;
    }

    if (read(pipes[process_num][0], &y, sizeof(int)) != -1) 
    {

        printf("Dernier read\n");
        return 3;
    }

    printf("The final result is %d\n", y);
    

    

    close(pipes[0][1]);
    close(pipes[process_num][0]);

    for (i = 0; i < process_num; i++) 
    {
        wait(NULL);
    }
    return 0;
}


int main(int argc, char *argv[], char *env[])
{


    char *tab_cmd_test2[4];

    tab_cmd_test2[0] = "ls";
    tab_cmd_test2[1] = "grep a";
    tab_cmd_test2[2] = "wc";
    tab_cmd_test2[3] = NULL;


    ms_pipe3(3, tab_cmd_test2, env);


    return 0;
}