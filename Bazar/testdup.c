#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



#define MAX_COMMAND_LENGTH 1024

void execute_command(char *command, char *output_command) {
    int fd[2];
    pid_t pid;

    char *output_file = NULL;
    char *command_parts[2];
    int command_part_index = 0;

    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '>') {
            // La commande contient une redirection de sortie
            output_file = &command[i + 1];
            while (*output_file == ' ') output_file++;
            break;
        } else if (command[i] == ' ') {
            command[i] = '\0';
            command_parts[command_part_index++] = &command[i + 1];
            while (*command_parts[command_part_index - 1] == ' ') command_parts[command_part_index - 1]++;
        }
    }
    command_parts[command_part_index] = NULL;

    if (output_file != NULL) {
        // La commande contient une redirection de sortie
        int out_fd = open(output_file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
        if (out_fd == -1) {
            perror("Erreur : impossible d'ouvrir le fichier de sortie");
            return;
        }

        pid = fork();
        if (pid == 0) {
            // Processus enfant : executer la commande et rediriger la sortie vers le fichier
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
            execvp(command, command_parts);
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("Erreur : impossible de creer un nouveau processus");
            return;
        } else {
            wait(NULL);
        }

        close(out_fd);

        // Utiliser la commande de sortie sur le fichier
        sprintf(output_command, "%s %s", output_command, output_file);
    } else {
        // La commande ne contient pas de redirection de sortie
        pipe(fd);

        pid = fork();
        if (pid == 0) {
            // Processus enfant : executer la commande et rediriger la sortie vers le tube
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]);
            execvp(command, command_parts);
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("Erreur : impossible de creer un nouveau processus");
            return;
        } else {
            // Processus parent : lire le resultat depuis le tube
            wait(NULL);
            close(fd[1]);
            char buffer[MAX_COMMAND_LENGTH];
            int bytes_read = read(fd[0], buffer, MAX_COMMAND_LENGTH);
            if (bytes_read == -1) {
                perror("Erreur : impossible de lire depuis le tube");
                return;
            }

            // Stocker le resultat dans la commande de sortie
            buffer[bytes_read] = '\0';
            sprintf(output_command, "%s %s", output_command, buffer);
        }
    }
}

void shell_command(const char* command) {
    char* args[256];
    char* output_files[256];
    int num_args = 0;
    int num_output_files = 0;
    int is_output_redirection = 0;
    char* token = strtok((char*) command, " ");
    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            is_output_redirection = 1;
        } else if (is_output_redirection) {
            output_files[num_output_files++] = token;
            is_output_redirection = 0;
        } else {
            args[num_args++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[num_args] = NULL;
    output_files[num_output_files] = NULL;

    int fd;
    for (int i = 0; output_files[i] != NULL; i++) {
        fd = open(output_files[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
        if (fd < 0) {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2");
            exit(1);
        }
    }

    execvp(args[0], args);
    perror("execvp");
    exit(1);
}


int main() {
    char test[] = "ls > a";
    shell_command(test);

    return 0;
}
