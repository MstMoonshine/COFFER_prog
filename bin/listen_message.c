#include <manager.h>
#include <stdlib.h>
#include <stdio.h>

#define LEN 0x10
#define EID 1 // Solve this! Hardcoded EID!

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Usage: %s [path_to_payload]\n", argv[0]);
		exit(0);
	}

	char volatile *buf = (char *)malloc(LEN);
	start_channel(EID, buf, LEN);	 // Solve this! Hardcoded EID!

	unsigned int id = createEnclave(argv[1], -1);

	printf("Back from the enclave\n");

	while (*buf == 0);
	printf("Message Received!\n");
	for (int i = 0; i < LEN; i++) {
		printf("0x%x\t", buf[i]);
	}
	printf("\n");

	resume_enclave(EID); // Solve this! Hardcoded EID!

	printf("Back from the enclave again\n");
	for (int i = 0; i < LEN; i++) {
		buf[i] = i;
	}
	send_message(EID, buf, LEN); // Solve this! Hardcoded EID!
	resume_enclave(EID);

	if (id >= 0) {
		printf("Enclave created successfully, id = %u\n", id);
	} else {
		printf("Enclave creation failed");
	}
}