#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <time.h>
#include <Windows.h>

#define SHIFT 0x01
#define XOR 0x02
#define SUB 0x03
#define FLIP 0x04
//Modes
#define DEBUG 0x01
#define DECRIPT 0x02
#define ENCRIPT 0X04

#define ACTION_KEY_SIZE 500
#define DATA_BUFFER_SIZE 255

//Mode Errors
#define ERROR_NO_MODE "There is No Mode for : i% :", MODE


//use the mod thing on the pass baced on the round 1,3,4,2 pow(char[0],char[1]) % getPrime()
typedef unsigned char byte;

typedef struct Action {
	byte com;
	byte at1;
	byte at2;
} Action;

typedef struct Key {
	char c;
	
	Action Act[ACTION_KEY_SIZE];
	
} Key;

class RoboFile
{
public:
	RoboFile();

	Key KeyLookUp(byte t);
	void closeRoboFile();
	
};

void Progress(const char label[], long step, long total);

