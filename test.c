#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *str1 = strdup("Je Victor suis");
    char *str = str1;

    char *str2 = str1;

    str1 += 3;
    str2 += 10;

    printf("%s\n", str);
    memmove(str1, str2, 4);
    printf("%s\n", str);
    return 0;
}
