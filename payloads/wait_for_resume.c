#include <payload.h>

int main()
{
	iprintf("Wait for resume");
	suspend_enclave();
}