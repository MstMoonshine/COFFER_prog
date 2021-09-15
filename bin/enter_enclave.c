#include <manager.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s [enclave id]\n", argv[0]);
		exit(0);
	}

	unsigned int id = atoi(argv[1]);
	enterEnclave(id);
	
	exit(0);
}