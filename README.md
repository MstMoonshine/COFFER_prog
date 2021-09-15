# COFFER_prog

API and demo programs for COFFER TEE.

## Components

```
.
├── bin						# Linux programs
│   ├── create_enclave.c
│   ├── enter_enclave.c
│   ├── Makefile
│   └── test.c
├── include					# COFFER API
│   ├── manager
│   │   └── manager.h
│   └── payload
│       └── payload.h
├── lib						# Static library source files
│   ├── Makefile
│   ├── manager.c
│   └── payload.c
├── Makefile
├── payloads					# Enclave payload ELFs 
│   ├── Makefile
│   ├── testpayload.c
│   └── write.c
└── README.md
```

- `bin`: Linux programs that managers the enclaves.
- `include`: Header files for linux programs and enclave payloads, in which COFFER APIs are defined.
- `lib`: Static library for linux programs and enclave payloads.
- `payloads`: ELFs to be loaded into enclaves.


## Usage

1. Write your programs in `bin` and `payloads` for Linux programs and enclave payloads respectively.

2. Build:

Make sure you have RISC-V GNU Toolchain installed, then
```
make
```

3. Copy the directory to your RISC-V device.

4. Run the programs.

## COFFER API

(To be finished...)