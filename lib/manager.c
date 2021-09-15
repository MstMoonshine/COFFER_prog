#include "../include/manager/manager.h"

int readFile(const char* path, char** data)
{
    int fd = -1;
    int ret = 1;
    long len = 0;
    fd = open(path, O_RDONLY);
    if (-1 == fd) {
        extern int errno;
        printf("File %s open failed\n", path);
        printf("ERROR: %d", errno);
        return -1;
    }

    len = lseek(fd, 0L, SEEK_END);
    lseek(fd, 0L, SEEK_SET);

    *data = malloc(len);
    len = 0;
    while (ret) {
        ret = read(fd, *data + len, 1024);
        if (ret == -1) {
            printf("File %s read failed\n", path);
            close(fd);
            free(*data);
            return -1;
        }
        len += ret;
    }
    close(fd);
    return len;
}

unsigned int createEnclave(const char* path, uintptr_t bitmask)
{
    char* payload;
    unsigned int len = readFile(path, &payload), eid;
    register uintptr_t a0;

    if (len == -1)
        exit(-1);

    // printf("Enclave created using payload: %s\n", path);

    // printf("a7 = 0x19260817, a6 = 399\n");
    SBI_CALL5(0x19260817, payload, len, bitmask, 399);
    asm volatile("mv %0,a0"
                 : "=r"(eid));
    free(payload);
    return eid;
}

void enterEnclave(unsigned int id)
{
    SBI_CALL5(0x19260817, id, 0, 0, 400);
    // SBI_CALL5(0x19260817, id, 0, 0, 404);
    return;
}

void exitEnclave(unsigned int id)
{
    SBI_CALL(401, id, 0, 0);
    return;
}

void dumpLayout()
{
    SBI_CALL5(0xdeadbeef, 0, 0, 0, 1);
}

long int gettime()
{
    int fd = open("/dev/mem", O_SYNC);
    uintptr_t* rtc = mmap(NULL, 0x1000, PROT_READ, MAP_PRIVATE, fd, 0x101000);

    long int usec = *rtc / 1000;

    return usec;
}

void resume(int id)
{
    SBI_CALL5(0x19260817, id, 0, 0, 404);
}