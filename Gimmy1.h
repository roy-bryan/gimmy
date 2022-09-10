#include "GimmyTriplet.h"

template<typename T>
class Gimmy1
{
private:
	GimmyTriplet<T>* triplet;
	int outBits;
	
	int numberOfBitsUsed(T);
	T firstUsedBits(T, int);
	T lastBits(T, int);
	T generatePart(T, int, int);
public:
	Gimmy1(int outputBits);
	
	T hash(T);
};