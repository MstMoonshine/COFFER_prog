#include <unistd.h>

int main() {
	const char str[] = "This is inside enclave COMPASS\n";
	write(1, str, sizeof(str)/sizeof(char));
	return -1;
}
