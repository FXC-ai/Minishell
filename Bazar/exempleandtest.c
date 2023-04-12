#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

void execute_command(char **parsed_args, int in_fd, int out_fd) {
    if (fork() == 0) {
        if (in_fd != STDIN_FILENO) {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd != STDOUT_FILENO) {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        execvp(parsed_args[0], parsed_args);
        perror(parsed_args[0]);
        exit(1);
    }
}

void proces_redirections(char **parsed_args) {
    int fds[2], in_fd = STDIN_FILENO, out_fd = STDOUT_FILENO;
    char **current_command = parsed_args;



    while (*parsed_args) {
        if (strcmp(*parsed_args, ">") == 0) {

            *parsed_args = NULL;
            out_fd = open(*(parsed_args + 1), O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (out_fd == -1) {
                perror(*(parsed_args + 1));
                exit(1);
            }
        } else if (strcmp(*parsed_args, "<") == 0) {
            *parsed_args = NULL;
            in_fd = open(*(parsed_args + 1), O_RDONLY | O_CREAT);

            if (in_fd == -1) {
                perror(*(parsed_args + 1));
                exit(1);
            }
        }
        parsed_args++;
    }

    execute_command(current_command, in_fd, out_fd);

    if (in_fd != STDIN_FILENO) {
        close(in_fd);
    }
    if (out_fd != STDOUT_FILENO) {
        close(out_fd);
    }
    wait(NULL);
    printf("Out fd %d\n", out_fd);
}

int main() {

    //printf("%d\n", strcmp(">", ">"));
   /* char *str[7] = {"echo", "Hello", ">", "hellofile.txt", ">", "hellofile2.txt", NULL};
    char *str2[4] = {"cat", "<", "tests", NULL};
    proces_redirections(str);*/
    /*int fds = open("test", O_WRONLY | O_CREAT | O_TRUNC, 0644);//fd[0] == read, fd[1] == write
    int id = fork();
    if (id == -1)
    {
        perror("fork");
        return (1);
    }
    else if (id == 0)
    {
        char x;
        printf("Input a char: ");
        scanf("%c", &x);
        write(fds, &x, sizeof(char));
        close(fds);
    } else {
        printf("WAIT\n");
        wait(0);
        sleep(2);
        printf("END WAIT\n");
        char y;
        fds = open("test", O_RDONLY, 0777);
        read(fds, &y, sizeof(char));
        close(fds);
        printf("Got from Child process %c\n", y);
    }*/

    return 0;
}