target_dir := ../build/payloads
lib_dir := ../build/lib
head_dir := ../include/payload

CC := riscv64-unknown-elf-gcc
CXX := riscv64-unknown-elf-g++
FLAGS := -g -O0 -static -L$(lib_dir) -lenclavepayload -I$(head_dir) -lm

src := $(wildcard *.c)
targets := $(src:.c=)
cpp_src := $(wildcard *.cc)
targets += $(cpp_src:.cc=)

all: dir $(addprefix $(target_dir)/, $(targets))

dir:
	mkdir -p $(target_dir)

$(target_dir)/%: %.c
	$(CC) $< -o $@ $(FLAGS)

$(target_dir)/%: %.cc
	$(CXX) $< -o $@ $(FLAGS)
