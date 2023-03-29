#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "includes/header.h"
struct termios saved;

/*void restore(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &saved);
}*/


int main() {
   /* struct termios attributes;

    printf("%s\n", ttyname(0));
    printf("%s\n", ttyname(1));
    printf("%d\n", ttyslot());


    tcgetattr(STDIN_FILENO, &saved);
    atexit(restore);

    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag &= ~ ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
    printf("%s\n", ttyname(0));
    printf("%s\n", ttyname(1));
    printf("Entering the loop\n");
    while(1) {};*/

    char *str1 = "dadwvar=test";
    char *str2 = "var";

    printf("%s", ft_strnstr(str1, str2, ft_strlen(str1)));

}
