#include <stdio.h>
#include <unistd.h>

int main() 
{
    char *filename = "lolo";
    if (unlink(filename) != 0) {
        perror("unlink() a échoué");
        return 1;
    } else {
        printf("Le fichier a été supprimé avec succès.\n");
    }
    return 0;
}