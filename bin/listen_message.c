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
	unsigned int eid = 1;
	createEnclave(argv[1], -1);

	printf("enclave created: eid = %u\n", eid);

	char volatile *buf = (char *)malloc(LEN);
	start_channel(eid, buf, LEN);

	enterEnclave(eid, 0, NULL);

	printf("Back from the enclave\n");
	while (*buf == 0);
	printf("Message Received!\n");
	for (int i = 0; i < LEN; i++) {
		printf("0x%x\t", buf[i]);
	}
	printf("\n");

	char* payload;
	unsigned int emod_len = readFile("/drv_mmc.bin",
		&payload);
	send_message(eid, payload, emod_len);

	resume_enclave(eid);
}