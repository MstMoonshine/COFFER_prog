#include <manager.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        printf("Usage: %s [enclave id] [args]\n", argv[0]);
        exit(0);
    }

    unsigned int id = atoi(argv[1]);
    enterEnclave(id, argc - 1, argv + 1);

    exit(0);
}