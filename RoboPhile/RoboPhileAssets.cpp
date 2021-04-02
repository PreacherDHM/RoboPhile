#include "RoboPhileAssets.h"


FILE* roboPhileFile;


RoboFile::RoboFile()
{
	FILE* tmp;
	fopen_s(&tmp, "RoboPhile.robo", "rb");
	if (tmp == NULL) {
		printf("Could not read RoboPhile.robo");
		
	}
	

	roboPhileFile = tmp;
	if (roboPhileFile == NULL) {
		printf("Could not read RoboPhile.robo");

	}
}

Key RoboFile::KeyLookUp(byte t)
{
	Key key;
	if (roboPhileFile == NULL) {
		printf("\nNUll");
	}
	fseek(roboPhileFile, sizeof(Key) * t, SEEK_SET);
	
	fread_s(&key, sizeof(Key), sizeof(Key), 1, roboPhileFile);
	
	return key;
}



void RoboFile::closeRoboFile()
{
	
	fclose(roboPhileFile);
}

void Progress(const char label[], long step, long total)
{
	//progress width
	const int pwidth = 50;

	//minus label len
	int width = pwidth - strlen(label);
	int pos = (step * width) / total;


	int percent = (step * 100) / total;


		
	printf("\r%s[", label);

	for (int i = 0; i < pos; i++) {
		printf("%c", 0x06);
	}
		
	
	printf("% *c", width - pos + 1, ']');
	printf("%3d%%", percent);

	fflush(stdout);
	


}
