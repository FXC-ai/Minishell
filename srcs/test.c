#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void) {
    int pipe1[2], pipe2[2];
    pid_t pid;

    if (pipe(pipe1) == -1) {
        perror("Erreur lors de la création de pipe 1");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe2) == -1) {
        perror("Erreur lors de la création de pipe 2");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1) {
        perror("Erreur lors de la création d'un nouveau processus");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Premier enfant
        close(pipe1[0]); // Ferme la fin de lecture de pipe1
        dup2(pipe1[1], STDOUT_FILENO); // Redirige la sortie standard vers pipe1
        close(pipe1[1]); // Ferme la fin d'écriture de pipe1

        execlp("ls", "ls", "-al", NULL); // Exécute la commande ls -al
        perror("Erreur lors de l'exécution de la commande ls"); // En cas d'erreur
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1) {
        perror("Erreur lors de la création d'un nouveau processus");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Deuxième enfant
        close(pipe1[1]); // Ferme la fin d'écriture de pipe1
        dup2(pipe1[0], STDIN_FILENO); // Redirige l'entrée standard depuis pipe1
        close(pipe1[0]); // Ferme la fin de lecture de pipe1

        close(pipe2[0]); // Ferme la fin de lecture de pipe2
        dup2(pipe2[1], STDOUT_FILENO); // Redirige la sortie standard vers pipe2
        close(pipe2[1]); // Ferme la fin d'écriture de pipe2

        execlp("grep", "grep", "test", NULL); // Exécute la commande grep test
        perror("Erreur lors de l'exécution de la commande grep"); // En cas d'erreur
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1) {
        perror("Erreur lors de la création d'un nouveau processus");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Troisième enfant
        close(pipe2[1]); // Ferme la fin d'écriture de pipe2
        dup2(pipe2[0], STDIN_FILENO); // Redirige l'entrée standard depuis pipe2
        close(pipe2[0]); // Ferme la fin de lecture de pipe2

        execlp("wc", "wc", "-l", NULL); // Exécute la commande wc -l
        perror("Erreur lors de l'exécution de la commande wc"); // En cas d'erreur
        exit(EXIT_FAILURE);
    }

    // Processus parent
    close(pipe1[0]); // Ferme la fin de lecture de pipe1
    close(pipe1[1]); // Ferme la fin d'écriture de pipe1
    close(pipe2[0]); // Ferme la fin de lecture de pipe2
    close(pipe2[1]); // Ferme la fin d'éc
}