#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <readline/readline.h>
#include <readline/history.h>


void demo_readline_addhistory ()
{
    printf("Demo readline\n");


    char *line;

    // gcc <nom_du_fichier>.c -lreadline
    line = readline("Entrez une chaîne: ");

    
    if (line && *line) {
        add_history(line);
        printf("Vous avez entré: %s\n", line);
    }

    // L'utilisateur est responsable de free le pointeur
    // renvoyé par la fonction readline
    free(line);
}


void demo_fork_wait()
{

    printf("Demo fork\n");

    pid_t pid;
    static int fork_count;
    int wait_status;

    pid = fork();
    fork_count++;
    // la fonction fork crée un processus enfant qui est exécuté en meme temps
    // que le processus parent. On les diferencie grace au pid :
    //          - pid = 0 => on est dans le processus enfant
    //          - pid > 0 => on est dans le processus parent
    if (pid == 0)
    {
        printf("Je suis le procesus fils du fork %d\n", fork_count);
    }
    else
    {
        // wait permet d attendre la fin du processus enfant avant d'executer
        // le processus enfant
        wait(&wait_status);
        printf("Je suis le processus parent du fork %d\n", fork_count);
    }

}


void demo_sigaction()
{



}



int main(void) {
    
    int i;

    demo_readline_addhistory();


    demo_fork_wait();


    struct sigaction sa;

    sa.sa_handler = han




    return 0;
}