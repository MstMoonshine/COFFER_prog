#include "../include/manager/manager.h"
#include "../include/ebi_ecall.h"
#include "../include/types.h"

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
    volatile register uintptr_t a0;

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

void enterEnclave(unsigned int id, int argc, char** argv)
{
    SBI_CALL5(0x19260817, id, argc, argv, 400);
    return;
}

void exitEnclave(unsigned int id)
{
    SBI_CALL(401, id, 0, 0);
    return;
}

long int gettime()
{
    int fd = open("/dev/mem", O_SYNC);
    uintptr_t* rtc = mmap(NULL, 0x1000, PROT_READ, MAP_PRIVATE, fd, 0x101000);

    long int usec = *rtc / 1000;

    return usec;
}

void suspend_enclave(int id)
{
    SBI_CALL5(0x19260817, id, 0, 0, 403);
}

void resume_enclave(int id)
{
    SBI_CALL5(0x19260817, id, 0, 0, 404);
}

void dump_enclave_status()
{
    printf("Currently %d enclaves:\n", enclave_num());
    fflush(stdout);
    SBI_CALL5(0x19260817, 0, 0, 0, 499);
}

void dump_enclave_mem()
{
    SBI_CALL5(0x19260817, 2, 0, 0, 499);
}

void dump_hartid()
{
    SBI_CALL5(0x19260817, 1, 0, 0, 499);
}

int enclave_num()
{
    int count;
    volatile register uintptr_t a0;
    SBI_CALL5(0x19260817, 3, 0, 0, 499);
    asm volatile("mv %0,a0"
                 : "=r"(count));
    return count;
}

int compacted()
{
    int flag;
    volatile register uintptr_t a0;
    SBI_CALL5(0x19260817, 4, 0, 0, 499);
    asm volatile("mv %0,a0"
                 : "=r"(flag));
    return flag;
}

int check_alive(int eid)
{
    int status; // dead or alive
    volatile register uintptr_t a0;
    SBI_CALL5(0x19260817, 5, eid, 0, 499);
    asm volatile("mv %0,a0"
                 : "=r"(status));
    return status;
}

void dump_mem_usage()
{
    SBI_CALL5(0x19260817, 7, 0, 0, 499);
}

int module_register(const char* path, uintptr_t eid, uint32_t mod_id)
{
    char *module;
    unsigned int len = readFile(path, &module), ret;
    volatile register uintptr_t a0;

    if (len == -1) {
        printf("error reading");
        exit(-1);
    }

    SBI_CALL6(0x19260817, eid, module, len, mod_id, 450);
    asm volatile("mv %0,a0"
                 : "=r"(ret));

    free(module);
    return ret;
}

int start_channel(u64 sender_eid, u8 *buf, usize len)
{
    SBI_CALL5(0x19260817, sender_eid, (u64)buf, len, SBI_EXT_EBI_LISTEN_MESSAGE);

    return 0;
}

int send_message(u64 receiver_eid, u8 *buf, usize len)
{
    SBI_CALL5(0x19260817, receiver_eid, (u64)buf, len, SBI_EXT_EBI_SEND_MESSAGE);

    return 0;
}