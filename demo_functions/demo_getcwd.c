#include <stdio.h>
#include <unistd.h>




int main() 
{
    char cwd[1024];

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