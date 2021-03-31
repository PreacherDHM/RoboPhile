#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <vector>

namespace RoboPhile {



	//----Encript----
	class Encript {
	public:
		Encript();
		~Encript();
		void PassDive(const char* pass, int size, const char* fileName);
	private:

		void Cript(FILE* data, FILE* SBOX, FILE* outFile, const char* pass, unsigned int size, int rounds);
		void Round(const char* pass, int size,FILE* outFile, FILE* data, FILE* SBOX);
		void ReadFile(FILE* data);
		void ActOnRoboPhile();




	};
	//----Decript----
	class Decript {
	public:
		Decript();
		~Decript();

		void PassDive(const char* pass, int size, const char* fileName);

	private:

		void DeCript(FILE* data, FILE* SBOX, FILE* outFile, const char* pass, int size, int rounds);
		void Round(const char* pass, int size, FILE* outFile, FILE* data, FILE* SBOX);
		

	};
}

