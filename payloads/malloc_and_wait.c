#include <payload.h>
#include <stdlib.h>

#define BYTES_MAX_NUM (0x100000 * 200)
#define TYPE_NUM 27

int bytes[TYPE_NUM];
int total = 0;

int init()
{
	for (int i = 0; i < TYPE_NUM; i++) {
		bytes[i] = 1 << i;
	}
}

void main()
{
	init();

	while (total < BYTES_MAX_NUM) {
		if (total > 0 && randint() % 100 > 95) {
			// printf("die\n");
			// return;;
			;
		}

		int rand_num = bytes[randint() % TYPE_NUM];
		int *p;
		if (total + rand_num < BYTES_MAX_NUM) {
			p = (int *)malloc(rand_num);
			*p = 1;
		}
		total += rand_num;
		
		suspend_enclave();
	}

	return;
}