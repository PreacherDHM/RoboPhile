#include "RoboPhileAssets.h"
#include "RoboPhile.h"
#include <stdio.h>

int main(int argc, char** argv) {
	RoboPhile::Encript encript;
	RoboPhile::Decript decript;

	FILE* roboPhile = nullptr;
	FILE* data;

	std::string pass = "beer-";

	bool bencrypt = false;
	bool bdecrypt = false;
	std::string fname;
	
	

	printf("args %d\n",argc);
	for (size_t i = 0; i < argc; i++)
	{
		
		
		if (i == 1) {
			
			pass = argv[1];
			printf("password : %c : Number of Chars : %d :\n", pass, pass.length());
		}


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
		encript.PassDive(pass.c_str(), pass.length(), fname.c_str());
	}
	if (bdecrypt)
	{
		decript.PassDive(pass.c_str(), pass.length(), fname.c_str());
	}
	
	
	

	std::cin;
}