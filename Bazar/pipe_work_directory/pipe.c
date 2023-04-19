# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>


char	**ft_split(char const *s, char c);

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *) str);
		str++;
	}
	if ((char)c == *str)
		return ((char *)str);
	return (NULL);
}

int reverse_bit(int i)
{
    return (!(i));
}

void	error_exit(int code_error)
{
	perror("minishell");
	exit(code_error);
}

static int exist_redirection(char *cmd)
{
    return (ft_strchr(cmd, '>') != NULL || ft_strchr(cmd, '<') != NULL);
}

void	freemalloc(char **result, int j)
{
	while (j >= 0)
	{
		free(result[j]);
		result[j] = NULL;
		j--;
	}
	free(result);
}

int size_tab(char **tab)
{
    int i;

    i = 0;
    while(tab[i] != NULL)
        i++;
    return (i);
}

void ms_pipe(char *tab_cmd[2]) 
{
    int pid;
    int i;
    int pipefd[2];
    int pipe_status;
    char **cmd;

    pipe_status = pipe(pipefd);
    if (pipe_status == -1)
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
                printf("Faut appeler Victor\n");
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

                if (execve(cmd[0], cmd) == -1)
                {
                    freemalloc(cmd, size_tab(cmd));
                    error_exit(EXIT_FAILURE);
                }
            }
            exit(0);
        }
        
        i++;
    }
    

    wait(NULL);
    //printf("Tous les processus enfants sont terminés.\n");
}

int main (int argc, char *argv[])
{
    char    *tab_cmd[2];
    
    tab_cmd[0] = "/bin/ls > fichier";
    tab_cmd[1] = "/bin/ls";

    ms_pipe(tab_cmd);
    
    
    return 0;
}

