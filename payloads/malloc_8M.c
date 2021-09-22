#include <stdlib.h>

int main()
{
	int *p = (int *)malloc(2 * 1024 * 0x1000);
	*p = 1;
}