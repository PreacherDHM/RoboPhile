#include "RoboPhileAssets.h"
#include "RoboPhile.h"
#include <stdio.h>

int main(int argc, char** argv) {
	RoboPhile::Encript encript;
	RoboPhile::Decript decript;

	FILE* roboPhile = nullptr;
	FILE* data;

	const char *pass = "beer-";

	bool bencrypt = false;
	bool bdecrypt = false;
	std::string fname;

	printf("args %d\n",argc);
	for (size_t i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
		pass = argv[1];

		if (strcmp(argv[i], "-d") == 0) {
			bdecrypt = true;
		}
		if (strcmp( argv[i], "-e") == 0) {
			bencrypt = true;
		}
		if (i == argc - 1) {
			fname = argv[i];
		}
		
	}
	if (bencrypt) {
		encript.PassDive(pass, 5, fname.c_str());
	}
	if (bdecrypt)
	{
		decript.PassDive(pass, 5, fname.c_str());
	}
	
	
	

	std::cin;
}