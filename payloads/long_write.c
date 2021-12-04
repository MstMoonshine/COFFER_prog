#include <unistd.h>

#define MAXN 50000

int arr[MAXN];

int main() {
    int i, j;
    for (i = 0; i < MAXN; ++i) {
        arr[i] = MAXN - i;
    }
    for (i = 0; i < MAXN; ++i) {
        for (j = 0; j < MAXN; ++j) {
            if (arr[i] > arr[j]) {
                arr[i] ^= arr[j];
                arr[j] ^= arr[i];
                arr[i] ^= arr[j];
            }
        }
    }
	const char str[] = "This is inside enclave COMPASS\n";
	write(1, str, sizeof(str)/sizeof(char));
	return -1;
}
