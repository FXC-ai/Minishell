#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *ent;
    char *path = "."; // Chemin du répertoire à parcourir

    // Ouvre le répertoire
    dir = opendir(path);
    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return -1;
    }

    // Parcourt le contenu du répertoire
    while ((ent = readdir(dir)) != NULL) {
        printf("%s\n", ent->d_name);
    }

    // Ferme le répertoire
    closedir(dir);
    return 0;
}
