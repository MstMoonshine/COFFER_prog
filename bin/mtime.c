#include <stdio.h>
#include <manager.h>

int main()
{
	unsigned long mtime;
	SBI_CALL5(0x19260817, 8, 0, 0, 499);
	asm volatile("mv %0,a0"
                 : "=r"(mtime));
	printf("mtime: %ld\n", mtime);
    	return 0;
}