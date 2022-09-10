#include "GimmyTriplet.h"
class Gimmy1
{
private:
	GimmyTriplet<int>* triplet;
	int outBits;
	
	int numberOfBitsUsed(int);
	int firstUsedBits(int, int);
	int lastBits(int, int);
	int generatePart(int, int, int);
public:
	Gimmy1(int outputBits);
	
	int hash(int);
};