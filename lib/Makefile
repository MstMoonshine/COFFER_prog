target_dir := ../build/lib
build_dir := ../build

CROSS1 := riscv64-unknown-linux-gnu-
CROSS2 := riscv64-unknown-elf-

CC1 := $(CROSS1)gcc
CC2 := $(CROSS2)gcc

AR1 := $(CROSS1)ar
AR2 := $(CROSS2)ar

all: dir $(target_dir)/libenclavemanager.a $(target_dir)/libenclavepayload.a

dir:
	mkdir -p $(target_dir)

$(build_dir)/manager.o: manager.c
	$(CC1) -c $< -o $@

$(build_dir)/payload.o: payload.c
	$(CC2) -c $< -o $@

$(target_dir)/libenclavemanager.a: $(build_dir)/manager.o
	$(AR1) rcs $@ $<
	@rm $<

$(target_dir)/libenclavepayload.a: $(build_dir)/payload.o
	$(AR2) rcs $@ $<
	@rm $<

.PHONY: all dir