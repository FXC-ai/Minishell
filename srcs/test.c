#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

// Définition d'une macro pour un statut de fin
// particulier pour le fils (si on ne l'indique pas à la compilation
// avec -D CHILD_EXIT_CODE=[nombre], par défaut elle sera à 42 :
#ifndef CHILD_EXIT_CODE
# define CHILD_EXIT_CODE 42
#endif

// Définition d'une macro pour le statut de fin
// du fils auquel on s'attend
#define EXPECTED_CODE 42

// Routine du processus fils :
void	routine_fils(pid_t pid)
{
	printf("\e[36mFils : Coucou! Je suis le fils. PID recu de fork = %d\e[0m\n", pid);
	printf("\e[36mFils : Je sors avec le statut de fin %d.\e[0m\n", CHILD_EXIT_CODE);
	exit(CHILD_EXIT_CODE);
}

// Routine du processus pere :
void	routine_pere(pid_t pid)
{
	int	status;

	printf("Pere : Je suis le pere. PID recu de fork = %d\n", pid);
	printf("Pere : J'attends mon fils qui a le PID [%d].\n", pid);
	waitpid(pid, &status, 0); // Attendre le fils
// ou   wait(&status);
	printf("Pere : Mon fils est sorti avec le statut %d\n", status);
	if (WIFEXITED(status)) // Si le fils est sorti normalement
	{
		printf("Pere : Le statut de fin de mon fils est %d\n", WEXITSTATUS(status));
		if (WEXITSTATUS(status) == EXPECTED_CODE)
			printf("Pere : C'est le statut que j'attendais !\n");
		else
			printf("Pere : Je ne m'attendais pas a ce statut-la...\n");
	}
}

int	main(void)
{
	pid_t	pid; // Stocke le retour de fork

	pid = fork(); // Création d'un processus fils
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0) // Processus fils
		routine_fils(pid);
	else if (pid > 0) // Processus père
		routine_pere(pid);
	return (EXIT_SUCCESS);
}