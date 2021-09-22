#include <manager.h>

int main()
{
	printf("Currently %d enclaves:\n", enclave_num());
	dump_enclave_status();
	exit(0);
}