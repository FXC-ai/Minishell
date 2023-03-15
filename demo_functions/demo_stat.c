#include <stdio.h>
#include <sys/stat.h>

int main() 
{
    char *filename = "../lolo";
    struct stat file_stat;
    if (stat(filename, &file_stat) != 0) 
	{
        perror("stat() a échoué");
        return 1;
    } 
	else 
	{
        printf("Taille du fichier : %lld octets\n", file_stat.st_size);
        printf("Dernière modification : %ld", file_stat.st_mtime);
    }
    return 0;
}