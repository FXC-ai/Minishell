#include <stdio.h>
#include <unistd.h>

int main() {
    if (isatty(STDOUT_FILENO)) {
        printf("La sortie standard est reliée à un terminal\n");
    } else {
        printf("La sortie standard n'est pas reliée à un terminal\n");
    }
    return 0;
}