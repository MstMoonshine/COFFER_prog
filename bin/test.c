#include <manager.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s [path_to_payload]\n", argv[0]);
		exit(0);
	}

	unsigned int id = createEnclave(argv[1], -1);
	enterEnclave(id);
}