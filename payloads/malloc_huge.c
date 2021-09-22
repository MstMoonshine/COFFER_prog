#include <stdlib.h>

int main()
{
	int *p = (int *)malloc(300 * 0x100000);
	*p = 1;
}