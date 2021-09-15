target_dir := ../build/bin
lib_dir := ../build/lib
head_dir := ../include/manager

CC := riscv64-unknown-linux-gnu-gcc
FLAGS := -I$(head_dir) -L$(lib_dir) -lenclavemanager -g -O0 -static

src := $(wildcard *.c)
targets := $(src:.c=)

all: dir $(addprefix $(target_dir)/, $(targets))

dir:
	mkdir -p $(target_dir)

$(target_dir)/%: %.c
	$(CC) $< -o $@ $(FLAGS) 