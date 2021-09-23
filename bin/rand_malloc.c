#include <manager.h>
#include <stdio.h>

#define ENC_MAX 160

int main(int argc, char *argv[])
{
	static long turn = 1;
	static long i = 3;
	static long eid[ENC_MAX] = {1};

	if (argc != 2) {
		printf("Usage: %s [enc number]\n", argv[0]);
		exit(0);
	}
	const int max = atoi(argv[1]);


	for (i = 0; i < max; i++) {
		eid[i] = i + 1;
	}

	while (1) {
		printf("turn %d\n", turn++);
		fflush(stdout);
		for (i = 0; i < max; i++) {
			int alive = check_alive(eid[i]);
			if (!alive) {
				eid[i] = createEnclave("../payloads/malloc_and_wait", -1);
				enterEnclave(eid[i]);
			} else {
				printf("resume %ld\n", eid[i]);
				fflush(stdout);
				resume_enclave(eid[i]);
			}
			dump_enclave_status();
			dump_enclave_mem();
		}
	}
}