#ifndef UTIL_H
#define UTIL_H

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <unistd.h>

#define SBI_CALL(___which, ___arg0, ___arg1, ___arg2) ({     \
    register uintptr_t a0 asm("a0") = (uintptr_t)(___arg0);  \
    register uintptr_t a1 asm("a1") = (uintptr_t)(___arg1);  \
    register uintptr_t a2 asm("a2") = (uintptr_t)(___arg2);  \
    register uintptr_t a7 asm("a7") = (uintptr_t)(___which); \
    asm volatile("ecall"                                     \
                 : "+r"(a0)                                  \
                 : "r"(a1), "r"(a2), "r"(a7)                 \
                 : "memory");                                \
})

#define SBI_CALL5(___which, ___arg0, ___arg1, ___arg2, ___arg3) ({ \
    register uintptr_t a0 asm("a0") = (uintptr_t)(___arg0);        \
    register uintptr_t a1 asm("a1") = (uintptr_t)(___arg1);        \
    register uintptr_t a2 asm("a2") = (uintptr_t)(___arg2);        \
    register uintptr_t a6 asm("a6") = (uintptr_t)(___arg3);        \
    register uintptr_t a7 asm("a7") = (uintptr_t)(___which);       \
    asm volatile("ecall"                                           \
                 : "+r"(a0)                                        \
                 : "r"(a1), "r"(a2), "r"(a6), "r"(a7)              \
                 : "memory");                                      \
})

#define SBI_CALL6(___which, ___arg0, ___arg1, ___arg2, ___arg3, ___arg4) ({			\
	register uintptr_t a0 asm ("a0") = (uintptr_t)(___arg0);	\
	register uintptr_t a1 asm ("a1") = (uintptr_t)(___arg1);	\
	register uintptr_t a2 asm ("a2") = (uintptr_t)(___arg2);	\
	register uintptr_t a3 asm ("a3") = (uintptr_t)(___arg3);	\
	register uintptr_t a6 asm ("a6") = (uintptr_t)(___arg4);	\
	register uintptr_t a7 asm ("a7") = (uintptr_t)(___which);	\
	asm volatile ("ecall"					\
		      : "+r" (a0)				\
		      : "r" (a1), "r" (a2), "r" (a3), "r" (a6), "r" (a7)		\
		      : "memory");				\
})

#define read_csr(reg) ({ unsigned long __tmp; \
	asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
	__tmp; })

int readFile(const char* path, char** data);
unsigned int createEnclave(const char* path, uintptr_t bitmask);
void enterEnclave(unsigned int id, int argc, char** argv);
void exitEnclave(unsigned int id);
long int gettime();
void suspend_enclave(int id);
void resume_enclave(int id);
void dump_hartid();
void dump_enclave_status();
void dump_enclave_mem();
int enclave_num();
int compacted();
int check_alive(int eid);
void dump_mem_usage();
int module_register();

#endif
