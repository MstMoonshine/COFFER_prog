#include <manager.h>
#include <stdlib.h>
#include <stdio.h>

#define LEN 0x10

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s [path_to_payload]\n", argv[0]);
		exit(0);
	}

	char volatile *buf = (char *)malloc(LEN);
	start_channel(1, buf, LEN);	

	unsigned int id = createEnclave(argv[1], -1);

	while (*buf == 0);
	printf("Message Received!\n");
	for (int i = 0; i < LEN; i++) {
		printf("0x%x\n", buf[i]);
	}

	if (id >= 0) {
		printf("Enclave created successfully, id = %u\n", id);
	} else {
		printf("Enclave creation failed");
	}
}