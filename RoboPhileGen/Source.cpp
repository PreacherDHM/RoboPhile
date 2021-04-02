#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include "RoboPhileAssets.h"


byte randCom(char target) {

	const char t[3] = { SHIFT,XOR,FLIP };
	//const char t[3] = { SHIFT,XOR,FLIP };
	int r = rand() % 3;
	return t[r];
}



void randAt(Action* act) {


	switch (act->com)
	{
	case SHIFT:
		act->at1 = (byte)((rand() % 0x03) + 0x01);
		act->at2 = (byte)((rand() % 0x02) + 0x01);
		break;
	case XOR:
		act->at1 = (byte)(rand() % 0xff);
		act->at2 = 0;
		break;
	case SUB:
		act->at1 = 0x00;
		act->at2 = 0x00;
		break;
	case FLIP:
		act->at1 = 0x00;
		act->at2 = 0x00;
		break;


	default:
		act->at1 = 0x00;
		act->at2 = 0x00;
		break;
	}
}

Action setAction(Action* pervAct, char target) {

	Action act{ 0,0,0 };
	byte tempCom = randCom(target);
	while (pervAct->com == tempCom) {
		tempCom = randCom(target);
	}

	act.com = tempCom;

	randAt(&act);
	printf("\nSet Action :: [%c] ([%c] [%c])  ::", act.com, act.at1, act.at2);
	return act;
}
Action setAction(char target) {

	Action act{ 0,0,0 };
	act.com = randCom(target);
	randAt(&act);
	printf("\nSet Action :: [%c] ([%c] [%c])  ::", act.com, act.at1, act.at2);
	return act;
}

void CreateKey(Key* key, char target) {
	key->c = target;
	for (size_t actionIndex = 0; actionIndex < ACTION_KEY_SIZE; actionIndex++)
	{
		if (actionIndex == 0) {
			key->Act[actionIndex] = setAction(target);
		}
		else
		{
			key->Act[actionIndex] = setAction(&key->Act[actionIndex - 1], target);
		}

	}



}

int CreatRoboPhile() {
	FILE* RoboPhile;

	Key key;

	srand(time(NULL));
	fopen_s(&RoboPhile, "RoboPhile.robo", "wb");
	if (RoboPhile == NULL) {
		printf("Could not Open file");
		return 1;
	}
	for (int i = 0; i < 128; i++) {
		CreateKey(&key, i);
		size_t elements_writen = fwrite(&key, sizeof(key), 1, RoboPhile);
		if (elements_writen == 0) {
			printf("Could not wright elements to file");
		}


	}

	fclose(RoboPhile);
	return 0;
}


int CreateSBOX() {
	FILE* SBOX;



	byte sBox[256] = { 0 };
	int wright = 0;
	bool found = false;
	bool up = false;




	fopen_s(&SBOX, "SBOX.robo", "wb");
	if (SBOX == NULL) {
		printf("Could not open File.");
		return 1;
	}

	srand(time(NULL));
	printf("\nWrighting to List...");
	for (int i = 0; i < 256; i++)
	{
		//printf("\nRound (%d)(%c)",i,i);

		int ri = rand() % 255;
		while (true) {


			if (sBox[ri] == NULL) {
				sBox[ri] = i;
				//printf("\nSet %c",i);
				break;
			}
			if (up) {
				if (ri < 256) {

					ri++;
				}
				else {
					up = false;
				}
			}
			else
			{
				if (ri > 0) {

					ri--;
				}
				else {
					up = true;
				}

			}

		}

	}
	printf("\nDone");
	printf("\nWrighting to File");
	fwrite(sBox, sizeof(sBox) / sizeof(byte), 1, SBOX);
	fseek(SBOX, 0, SEEK_SET);

	fclose(SBOX);
	printf("\nDone");
	return 0;
}


int main() {

	CreatRoboPhile();

	CreateSBOX();

	return 0;
}