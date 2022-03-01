#include <stdio.h>

int main(int argc, char** argv)
{
    int i;
    printf("argc = %d, argv = %p\n", argc, argv);
    for (i = 0; i < argc; ++i) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }
    return 0;
}