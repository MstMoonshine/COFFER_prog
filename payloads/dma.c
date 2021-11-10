#include <payload.h>

int main()
{
	register uintptr_t a7 asm ("a7") = (uintptr_t)(1234);
	uintptr_t a0 = 0;
	asm volatile ("ecall"
				: "+r" (a0)
				:: "memory");
}