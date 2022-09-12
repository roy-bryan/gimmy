#include <iostream>
#include <math.h>
#include <bitset>

#include "Gimmy1.cpp"
#include "Byte.cpp"

using namespace std;

unsigned int gimmy(unsigned int, int);

int numberOfBitsUsed(unsigned int);
unsigned int firstUsedBits(unsigned int, int);
unsigned int lastBits(unsigned int, int);

unsigned int generatePart(unsigned int, int, int);

unsigned int lastDiv(unsigned int p, unsigned int b, int length);
unsigned int lastProd(unsigned int a, unsigned int b, int length);

int main(int argc, char *argv[]) {
	int inputByte = atoi(argv[1]);
	int targetLength = atoi(argv[2]);
	
	if(targetLength == 0){ //If no second argument is given, or if it is zero, hash to a 32-bit value
		targetLength = 30;
	}
	
	//Hash integer
	Gimmy1<int> gmy(targetLength);
	
	cout << gmy.hash(inputByte) << endl;
	
	//Hash Byte
	Gimmy1<Byte> gmyB(targetLength);
	
	Byte inByte = inputByte;
	Byte hashedByte = gmy.hash(inputByte);
	cout << hashedByte.getNum() << endl;
	
	return 0;
}