#include "../include/payload/payload.h"

void dumpLayout()
{
    SBI_CALL5(0xdeadbeef, 0, 0, 0, 1);
}

void suspend()
{
    SBI_CALL5(0x19260817, 0, 0, 0, 403);
}