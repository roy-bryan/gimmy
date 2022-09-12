#include "GimmyTriplet.h"

template<typename T>
class Gimmy1
{
private:
	GimmyTriplet<T>* triplet;
	int outBits;
	
	int numberOfBitsUsed(const T&);
	T firstUsedBits(const T&, int);
	T lastBits(const T&, int);
	T generatePart(const T&, int, int);
public:
	Gimmy1(int outputBits);
	
	T hash(const T&);
};