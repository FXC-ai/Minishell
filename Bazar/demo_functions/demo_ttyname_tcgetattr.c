#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

int main() 
{
    struct termios term;
    char *name;

    if (tcgetattr(STDIN_FILENO, &term) < 0) {
        perror("Erreur lors de l'obtention des attributs du terminal");
        return -1;
    }

    name = ttyname(STDIN_FILENO);
    if (name == NULL) {
        perror("Erreur lors de l'obtention du nom du terminal");
        return -1;
    }

    printf("Le nom du terminal associé au descripteur de fichier est : %s\n", name);

    return 0;
}