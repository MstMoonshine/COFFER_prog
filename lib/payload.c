#include "../include/payload/payload.h"

void dumpLayout()
{
    SBI_CALL5(0xdeadbeef, 0, 0, 0, 1);
}

void suspend_enclave(int id)
{
    SBI_CALL5(0x19260817, id, 0, 0, 403);
}

int randint()
{
    static int32_t rand_state = 0;
    int32_t cycle = (int32_t)read_csr(cycle);

    if (rand_state == 0)
        rand_state = cycle;

    rand_state = ((rand_state * 1103515245) + 12345) & 0x7fffffff;

    return rand_state;
}