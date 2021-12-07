all:
	make -C lib
	make -C bin
	make -C payloads
	make -C coremark compile PORT_DIR=riscv64 OPATH=../build/payloads/

clean:
	@rm -rf build/*
