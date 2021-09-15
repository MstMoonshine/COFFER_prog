#include <manager.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s [path_to_payload]\n", argv[0]);
		exit(0);
	}

	unsigned int id = createEnclave(argv[1], -1);

	if (id >= 0) {
		printf("Enclave created successfully, id = %u\n", id);
	} else {
		printf("Enclave creation failed");
	}
}