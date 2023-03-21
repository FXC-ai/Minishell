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

void process_pipe_redirections(char **parsed_args) {
    int fds[2], in_fd = STDIN_FILENO, out_fd = STDOUT_FILENO;
    char **current_command = parsed_args;

    while (*parsed_args) 
    {
        if (strcmp(*parsed_args, "|") == 0) 
        {
            *parsed_args = NULL;
            pipe(fds);
            out_fd = fds[1];

            execute_command(current_command, in_fd, out_fd);

            close(out_fd);
            in_fd = fds[0];
            current_command = parsed_args + 1;
        } else if (strcmp(*parsed_args, ">") == 0) 
        {
            *parsed_args = NULL;
            out_fd = open(*(parsed_args + 1), O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (out_fd == -1) {
                perror("open");
                exit(1);
            }
        } else if (strcmp(*parsed_args, "<") == 0) {
            *parsed_args = NULL;
            in_fd = open(*(parsed_args + 1), O_RDONLY);

            if (in_fd == -1) {
                perror("open");
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
}

int main() {
   
char *str[7] = {"echo", "hello", ">", "test123", "|", "cat", NULL};
    process_pipe_redirections(str);
    return 0;
}