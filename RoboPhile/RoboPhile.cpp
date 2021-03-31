#include "RoboPhile.h"
#include "RoboPhileAssets.h"
#include <iostream>
#include <string>
#include <vector>




int getPrim(int input, const char pass[]) {
	const int primeList[16] = { 2,3,5,7,11,13,17,19,23,29,31,37,39,41,43,47 };
	return (input % (int)pass[0]) % sizeof(primeList) / sizeof(primeList[0]);
}

int getSiclow(byte a, byte b, int prime) {

	return ((int)(pow((int)a, (int)b)) % prime);

}

//----Operations----
byte OpShift(byte in, byte a, byte b, byte MODE = 0x00) {
	byte temp = NULL;

	if (MODE == ENCRIPT) {


		if (b == 0x01) {
			if (MODE == DEBUG) {
				printf("\n\tShift  ::  [in : %c] [a : %c] [b : %c]  :: Returning (%c)", in, a, b, temp);
			}
			temp = ((byte)in << 1) | (in >> 7);
			return temp;
		}
		else {
			if (MODE == DEBUG) {
				printf("\n\tShift  ::  [in : %c] [a : %c] [b : %c]  :: Returning (%c)", in, a, b, temp);
			}
			return ((byte)in >> 1) | (in << 7);
		}
	}
	if (MODE == DECRIPT){
		if (b == 0x01) {
			if (MODE == DEBUG) {
				printf("\n\tShift  ::  [in : %c] [a : %c] [b : %c]  :: Returning (%c)", in, a, b, temp);
			}

			return ((byte)in >> 1) | (in << 7);

		}
		else {
			if (MODE == DEBUG) {
				printf("\n\tShift  ::  [in : %c] [a : %c] [b : %c]  :: Returning (%c)", in, a, b, temp);
			}
			temp = ((byte)in << 1) | (in >> 7);
			return temp;
		}
	}else{
		printf(ERROR_NO_MODE);	
	}

}
byte OpXor(byte in, byte a, byte b, byte MODE = 0x00) {
	byte temp = in ^ a+1;
	if (MODE == DEBUG) {
		printf("\n\tXor    ::  [in : %c] [a : %c] [b : %c]  :: Returning (%c)",in,a,in,temp);
	}
	return temp;
}
byte OpSub(byte in, byte a, byte b, FILE* SBOX, byte MODE = 0x00) {

	size_t bytes_read = 0;
	char tmpchar;
	char nchar;
	int characterPosition = 0;

	
	if (MODE == ENCRIPT) {

		if (SBOX == NULL) {
			printf("Could not Reed from SBOX.robo");
			return in;
		}

		fseek(SBOX, (int)in, SEEK_SET);

		bytes_read = fread(&nchar, sizeof(nchar), 1, SBOX);
		if (bytes_read == 0) {
			printf("Could not read Bytes.");
			return a;
		}
		if (MODE == DEBUG) {
			printf("\n\tSUB    ::  [in : %c] [a : %c] [b : %c]  :: Returning (%c)", in, a, b, nchar);
		}
	}
	if (MODE == DECRIPT) {


		if (SBOX == NULL) {
			printf("Could Not Read from SBOX.robo");
			return in;
		}
		characterPosition = 0;
		
		while (true) {

			if (feof(SBOX)) {
				break;
			}
			fseek(SBOX, characterPosition, SEEK_SET);
			characterPosition++;

			size_t bytes_read = fread(&tmpchar, sizeof(tmpchar), 1, SBOX);


			if (in == tmpchar) {
				
				nchar = characterPosition;
				break;
			}
			else
			{
				//printf("\rNope :%c:", characterPosition);
			}
		}
		//printf("Found \n");
		//printf("Before %c Char \t return :%c:\n", in, characterPosition);

	}


	//printf("\nUsing Sub");
	return nchar;
}
byte OpFlip(byte in, byte a, byte b, byte MODE) {
	byte temp = (byte)(in ^ 255);
	if (MODE == DEBUG) {
		printf("\n\tFlip   ::  [in : %c] [a : %c] [b : %c]  :: Returning (%c)",in,a,b,temp);
	}
	return temp;
}


void getInstructions(const char pass[], int size, Action* actions, int* actionSize) {



	RoboFile rf;
	printf("\nCreated File");

	int actionSolection = 0;

	Key temp;




	for (size_t i = 0; i < size; i++)
	{

		temp = rf.KeyLookUp((byte)pass[i]);
		for (size_t ActionIndex = 0; ActionIndex < ACTION_KEY_SIZE; ActionIndex++)
		{
			actions[actionSolection] = temp.Act[ActionIndex];
			actionSolection++;
			//printf("\nActions Looked up ::  (%c)  ::", actions[actionSolection].com);

		}
		
	}


	//printf("\nDone");
}

byte* doActions(byte *input,  Action acts[],  int actionSize,int rounds, FILE* SBOX, int MODE, int inputSize = 0) {
	byte com = NULL;
	byte a = NULL;
	byte b = NULL;
	byte tmpinput = *input;

	byte pcom = NULL;
	
	byte mode = MODE;
	
	printf("\n\tinput beffor :: %c", (*input));
	
	
	for (size_t j = 0; j < rounds; j++)
	{
		
		
		for (int i = 0; i < actionSize; i++)
		{
		
			if (acts == NULL) {
				printf("acts == NUll");
			}

			com = acts[i].com;
			a = acts[i].at1;
			b = acts[i].at2;
			
			

			switch (com)
			{
			case SHIFT:
				tmpinput = OpShift(tmpinput, a, b, mode);
				break;
			case XOR:
				tmpinput = OpXor(tmpinput, a, b, mode);
				break;
			case SUB:
				tmpinput = OpSub(tmpinput, a, b, SBOX, mode);
				break;
			case FLIP:
				tmpinput = OpFlip(tmpinput, a, b, mode);
				break;

			default:
				//printf("\nDid not find Action (%x) ",com);
				break;

			}
			if (mode == DEBUG) {
				printf("  ::  Action Nuber (%d)", i);
			}
			
			
			//printf("\n%c",tmpinput);
			

		}
		
	}
	
	
	printf(" :: output %c", tmpinput);
	return &tmpinput;
	//printf("Finished with %c", tmpinput);
	
	//printf("\n\t output :: %c\n", (*input));
	
}


void doBufferActions(byte input[], Action acts[], int actionSize, int rounds, FILE* SBOX, int inputSize = 0) {
	byte com = NULL;
	byte a = NULL;
	byte b = NULL;
	

	byte pcom = NULL;

	byte mode = ENCRIPT;
	if (mode == DEBUG) {
		for (int i = 0; actionSize > i; i++) {
			printf("Action : %d :\n", acts[i].com);

		}
	}

	for (size_t j = 0; j < rounds; j++)
	{
		Progress("Encripting ", j, rounds);
		for (size_t k = 0; k < inputSize; k++)
		{
			for (int i = 0; i < actionSize; i++)
			{
			
			if (acts == NULL) {
				printf("acts == NUll");
			}

			com = acts[i].com;
			a = acts[i].at1;
			b = acts[i].at2;


			
				//printf("\n\tinput beffor :: %c", input[k]);
				switch (com)
				{
				case SHIFT:
					input[k] = OpShift(input[k], a, b, ENCRIPT);
					break;
				case XOR:
					input[k] = OpXor(input[k], a, b, ENCRIPT);
					break;
				case SUB:
					input[k] = OpSub(input[k], a, b, SBOX, ENCRIPT);
					break;
				case FLIP:
					input[k] = OpFlip(input[k], a, b, ENCRIPT);
					break;

				default:
					//printf("\nDid not find Action (%x) ", com);
					break;

				}
				if (mode == DEBUG) {
					//printf("  ::  Action Nuber (%d)", i);
				}
				
				
				
				//printf(" :: output %c", input[k]);
			}
			

			
			//printf("\n%c",tmpinput);

			
		}
		
		
	}


	
	
	//printf("Finished with %c", tmpinput);

	//printf("\n\t output :: %c\n", (*input));

}

void doBufferActionsRev(byte input[], Action acts[], int actionSize, int rounds, FILE* SBOX, int inputSize = 0) {
	byte com = NULL;
	byte a = NULL;
	byte b = NULL;
	int actionNumber = 0;

	byte pcom = NULL;

	byte mode = DECRIPT;
	if (mode == DEBUG) {
		for (int i = 0; actionSize > i; i++) {
			printf("Action : %d :\n", acts[i].com);

		}
	}



	for (size_t j = 0; j < rounds; j++)
	{
		Progress("Decrypting ", j, rounds);
		for (size_t k = 0; k < inputSize; k++)
		{
			for (int i = actionSize; i >= 0; i--)
			{
				
				actionNumber = i;
				if (acts == NULL) {
					printf("acts == NUll");
				}

				com = acts[i].com;
				a = acts[i].at1;
				b = acts[i].at2;



				//printf("\n\tinput beffor :: %c", input[k]);
				switch (com)
				{
				case SHIFT:
					input[k] = OpShift(input[k], a, b, DECRIPT);
					break;
				case XOR:
					input[k] = OpXor(input[k], a, b, DECRIPT);
					break;
				case SUB:
					input[k] = OpSub(input[k], a, b, SBOX, DECRIPT);
					break;
				case FLIP:
					input[k] = OpFlip(input[k], a, b, DECRIPT);
					break;

				default:
					//printf("\rDid not find Action (%x)\t ", com);
					break;

				}
				if (mode == DEBUG) {
					printf("  ::  Action Nuber (%d)\n", i);
				}



				//printf(" :: output %c", input[k]);
			}



			//printf("End of actions\n");


		}


	}
	//printf("\n");


	//printf("Finished with %c", tmpinput);

	//printf("\n\t output :: %c\n", (*input));

}

//----Encript----
RoboPhile::Encript::Encript()
{

}

RoboPhile::Encript::~Encript()
{

}

void RoboPhile::Encript::PassDive(const char* pass, int size, const char* fileName)
{
	printf(pass);
	

	FILE* data;
	FILE* SBOX;
	FILE* outFile;
	std::string fileN;
	fileN = fileName;
	fileN += +".robo";
	fopen_s(&data, fileName, "rb");
	fopen_s(&SBOX, "SBOX.robo", "rb");
	fopen_s(&outFile, fileN.c_str(),"wb");
	if ((outFile||SBOX||data) == NULL) {
		printf("can't read files");
		return;
	}
	else {
		printf("\nReading Files");
	}
	Round(pass, size, outFile, data,SBOX);
}

void RoboPhile::Encript::Round(const char* pass, int size, FILE* outFile, FILE* data, FILE* SBOX)
{
	
	//size_t rounds = size % getPrim(size, pass);
	size_t rounds = 4;
	printf("\n%d :: rounds", rounds);
	
	
		Cript(data,SBOX,outFile, pass, size, rounds);
		
	
}
//----Algrithem----
void RoboPhile::Encript::Cript(FILE* data, FILE* SBOX, FILE* outFile, const char* pass, unsigned int size,int rounds)
{
	
	byte targetFileBuffer[DATA_BUFFER_SIZE];

	for (size_t j = 0; j < DATA_BUFFER_SIZE; j++)
	{
		targetFileBuffer[j] = 1;
	}

	Action* actions = new Action[size * ACTION_KEY_SIZE];

	int actionGroupSize = size * ACTION_KEY_SIZE;
	int targetFileBufferSize = DATA_BUFFER_SIZE;
	//fseek(data, 0, SEEK_END);
	//int getfileSize = ftell(data);
	

	fseek(data, 0, SEEK_SET);
	//fseek(outFile, 0, SEEK_SET);
	getInstructions(pass, size, actions, &actionGroupSize);
	
	//printf("\n %c", actions[0].com);
	
		
		/*for(int i = 0; i < actionGroupSize; i++)
		{*/
		while(true){
			if (feof( data)) {
				break;
			}
			//printf("\nIncript");
			
			size_t Read_elemets = fread_s(&targetFileBuffer, DATA_BUFFER_SIZE, sizeof(byte), DATA_BUFFER_SIZE, data);
			
			printf("\nRead %d", Read_elemets);
			//printf("\ndefference || input %c", targetFileBuffer);
			
				
			//targetFileBuffer = *doActions(&targetFileBuffer, actions, actionGroupSize,rounds, SBOX);
			doBufferActions(targetFileBuffer, actions, actionGroupSize, rounds, SBOX,DATA_BUFFER_SIZE);
		
			
			
				
			fwrite(&targetFileBuffer, sizeof(byte), Read_elemets, outFile);
				
			
			
		}
	

	
	fclose(outFile);
	//targetFileBuffer = 0;
	printf("\nDone With File");
	delete[] actions;
}



//----Decript----

RoboPhile::Decript::Decript()
{
}

RoboPhile::Decript::~Decript()
{
}

void RoboPhile::Decript::PassDive(const char* pass, int size, const char* fileName)
{
	printf(pass);


	FILE* data;
	FILE* SBOX;
	FILE* outFile;
	std::string fileN;
	std::string deFile;
	deFile = fileName;
	deFile += ".d";
	fileN = fileName;
	fileN += +".robo";
	fopen_s(&data, fileN.c_str(), "rb");
	fopen_s(&SBOX, "SBOX.robo", "rb");
	fopen_s(&outFile, deFile.c_str(), "wb");

	if ((outFile || SBOX || data) == NULL) {
		printf("can't read files");
		return;
	}
	else {
		printf("\nReading Files");
	}
	Round(pass, size, outFile, data, SBOX);
}

void RoboPhile::Decript::DeCript(FILE* data, FILE* SBOX, FILE* outFile, const char* pass, int size, int rounds)
{
	byte targetFileBuffer[DATA_BUFFER_SIZE];

	for (size_t j = 0; j < DATA_BUFFER_SIZE; j++)
	{
		targetFileBuffer[j] = 0;
	}

	Action* actions = new Action[size * ACTION_KEY_SIZE];

	int actionGroupSize = size * ACTION_KEY_SIZE;
	int targetFileBufferSize = DATA_BUFFER_SIZE;



	fseek(data, 0, SEEK_SET);
	fseek(outFile, 0, SEEK_SET);
	getInstructions(pass, size, actions, &actionGroupSize);


	while (true) {
		if (feof(data)) {
			break;
		}
		//printf("\nIncript");

		size_t Read_elemets = fread_s(&targetFileBuffer, DATA_BUFFER_SIZE, sizeof(byte), DATA_BUFFER_SIZE, data);

		printf("\nRead %d", Read_elemets);
		//printf("\ndefference || input %c", targetFileBuffer);


		//targetFileBuffer = *doActions(&targetFileBuffer, actions, actionGroupSize,rounds, SBOX);
		doBufferActionsRev(targetFileBuffer, actions, actionGroupSize, rounds, SBOX, DATA_BUFFER_SIZE);




		fwrite(&targetFileBuffer, sizeof(byte), Read_elemets, outFile);



	}

	fclose(outFile);
	//targetFileBuffer = 0;
	printf("\nDone With File");
	delete[] actions;
}

void RoboPhile::Decript::Round(const char* pass, int size, FILE* outFile, FILE* data, FILE* SBOX)
{
	size_t rounds = 4;
	DeCript(data, SBOX, outFile, pass, size, rounds);

	

}



