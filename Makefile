all:
	make -C lib
	make -C bin
	make -C payloads

clean:
	@rm -rf build/*