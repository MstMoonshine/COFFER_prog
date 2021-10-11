#include <manager.h>
#include <stdio.h>

#define ENC_MAX 160

int main(int argc, char *argv[])
{
	volatile static long turn = 1;
	static long i = 3;
	static long eid[ENC_MAX] = {1};

	if (argc != 2) {
		printf("Usage: %s [enc number]\n", argv[0]);
		exit(0);
	}
	const int max = atoi(argv[1]);

	while (1) {
		// printf("turn %d\n", turn++);
		if (turn > 200)
			return 0;
		fflush(stdout);
		for (i = 0; i < max; i++) {
			int alive = check_alive(i + 1);
			if (!alive) {
				createEnclave("../payloads/malloc_and_wait", -1);
				enterEnclave(i + 1);
			} else {
				// printf("resume %ld\n", i + 1);
				fflush(stdout);
				resume_enclave(i + 1);
			}
			// dump_enclave_status();
			// dump_enclave_mem();
			dump_mem_usage();
		}
	}
}