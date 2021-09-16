#include <manager.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <error.h>

#define MAXN 3

uint32_t c_eid = 0;

void handler(int sig)
{
	switch (sig) {
	case SIGUSR1:
		dump_hartid();
		break;
	case SIGUSR2:
		printf("[Child] Entering enclave %d\n", c_eid);
		fflush(stdout);
		enterEnclave(c_eid);
		exit(0);
		break;
	default:
		printf("[Child] Invalid signal\n");
		break;
	}
}

int main()
{
	uint32_t eid[MAXN];
	pid_t pid[MAXN];

	printf("Parent hartid:\n");
	fflush(stdout);
	dump_hartid();
	
	for (int i = 0; i < MAXN; i++) {
		eid[i] = createEnclave("../payloads/write", -1);
	}

	for (int i = 0; i < MAXN; i++) {
		c_eid = eid[i];
		if (!(pid[i] = fork())) {
			printf("[Child] c_eid = %d\n", c_eid);
			fflush(stdout);

			signal(SIGUSR1, handler);
			signal(SIGUSR2, handler);
			while(1)
				pause();
		}
		printf("Child process created: pid = %d, eid = %u\n",
			pid[i], eid[i]);
		fflush(stdout);
	}

	for (int i = 0; i < MAXN; i++) {
		char buf[256];
		sprintf(buf, "taskset -cp %d %d", i + 1, pid[i]);
		system(buf);
	}

	printf("Dump CPU affinity\n");
	fflush(stdout);
	for (int i = 0; i < MAXN; i++) {
		int ret = kill(pid[i], SIGUSR1);
		if (ret == -1)
			perror("USR1 failed");
	}

	sleep(0.5);

	printf("Launch\n");
	fflush(stdout);
	for (int i = 0; i < MAXN; i++) {
		int ret = kill(pid[i], SIGUSR2);
		if (ret == -1)
			perror("USR2 failed");
	}
}