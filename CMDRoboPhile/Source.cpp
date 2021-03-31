
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <time.h>


//int main() {
//	FILE* sboxOut;
//	char sBox[256] = { 0 };
//	int wright = 0;
//	bool has = false;
//	bool up = false;
//	
//	
//	
//
//	fopen_s(&sboxOut, "SBOX.robo", "wb");
//	if (sboxOut == NULL) {
//		printf("Could not open File.");
//		return 1;
//	}
//
//	srand(time(NULL));
//	while (wright < 256) {
//		int a = rand() % 256;
//		int ta = a;
//
//
//		
//
//		for (size_t i = 0; i < 256; i++)
//		{
//			
//			if (up) {
//				a++;
//			}
//			else {
//				a--;
//			}
//
//			if (a == NULL) {
//				break;
//			}
//
//			//printf("\nNope: %c :: %x		", (char)a, a);
//			for (size_t i = 0; i < sizeof(sBox) / 4; i++)
//			{
//				if (!sBox[i] == (char)a) {
//					has = true;
//				}
//
//			}
//			
//
//			if (has == false) {
//				sBox[wright] = (char)a;
//				wright++;
//				
//				up ^= up;
//				break;
//			}
//			
//			if (a < 0 || a > 256) {
//				up ^= up;
//				break;
//			}
//
//			
//		}
//		printf("Found %c\n", (char)a);
//	}
//
//	
//	fwrite(sBox, sizeof(sBox), 1, sboxOut);
//	fseek(sboxOut, 0, SEEK_SET);
//
//	fclose(sboxOut);
//	return 0;
//}

