#include <stdio.h>
#include <unistd.h>

int main() 
{
    char cwd[1024];
    char *new_directory = "../";
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        printf("Le répertoire de travail actuel est : %s\n", cwd);
    } 
    else 
    {
        perror("getcwd() a échoué");
        return 1;
    }

    if (chdir(new_directory) != 0) {
        perror("chdir() a échoué");
        return 1;
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        printf("Le répertoire de travail actuel est : %s\n", cwd);
    } 
    else 
    {
        perror("getcwd() a échoué");
        return 1;
    }

    return 0;
}