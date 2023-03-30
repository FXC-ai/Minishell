#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cd(char *path) {
    int status = chdir(path);
    if (status != 0) {
        perror("cd");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        printf("Usage: %s directory\n", argv[0]);
        return EXIT_FAILURE;
    }

    chdir("dossierTest/");

    return 0;
}
