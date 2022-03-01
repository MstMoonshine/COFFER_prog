#include <manager.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc != 4) {
		printf("Usage: %s [eid] [module id] [path_to_module]\n", argv[0]);
		exit(0);
	}

	unsigned int id = atoi(argv[1]);
	unsigned int mod_id = atoi(argv[2]);

	if (module_register(argv[3], id, mod_id) < 0) {
		printf("register failed\n");
		exit(0);
	}
	
	return 0;
}