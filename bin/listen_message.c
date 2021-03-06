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

	char volatile *buf = (char *)malloc(LEN);
	start_channel(eid, buf, LEN);

	createEnclave(argv[1], -1);

	printf("Back from the enclave\n");
	while (*buf == 0);
	printf("Message Received!\n");
	for (int i = 0; i < LEN; i++) {
		printf("0x%x\t", buf[i]);
	}
	printf("\n");

	char* payload;
	unsigned int emod_len = readFile("/emodules/drv_mmc.bin",
		&payload);
	printf("emodule len = %u\n", emod_len);
	send_message(eid, payload, emod_len);

	resume_enclave(eid);
}