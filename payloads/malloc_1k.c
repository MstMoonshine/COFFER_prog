#include <stdlib.h>
#include <stdio.h>

int main()
{
	int *ptr = (int *)malloc(0x100);
	*ptr = 1;

	printf("Value: %d\n", *ptr);
	return 0;
}