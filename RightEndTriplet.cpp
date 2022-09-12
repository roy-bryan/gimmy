#ifndef RIGHT_END_TRIPLET
#define RIGHT_END_TRIPLET

#include <math.h>

#include "RightEndTriplet.h"

template<typename T>
RightEndTriplet<T>::RightEndTriplet(){ //Default constructor
	RightEndTriplet(32);
}

template<typename T>
RightEndTriplet<T>::RightEndTriplet(int n){ //Constructor
	numBits = n; //Set the number of bits to the specified value
	
	volatilityQueue[0] = &a;
	volatilityQueue[1] = &b;
	volatilityQueue[2] = &p;
}

template<typename T>
void RightEndTriplet<T>::setA(const T& n){ //Setter for a
	a = rightEnd(n, numBits); //Assign a to the value of n
	
	setLeastVolatile(&a);
	
	recalculateMostVolatile();
}

template<typename T>
void RightEndTriplet<T>::setB(const T& n){ //Setter for b
	b = rightEnd(n, numBits); //Assign b to the value of n
	
	setLeastVolatile(&b);
	
	recalculateMostVolatile();
}

template<typename T>
void RightEndTriplet<T>::setP(const T& n){ //Setter for p
	p = rightEnd(n, numBits); //Assign a to the value of n
	
	setLeastVolatile(&p);
	
	recalculateMostVolatile();
}

template<typename T>
void RightEndTriplet<T>::setLeastVolatile(T* field){ //Moves specified field to least volatile spot in queue
	if(volatilityQueue[0] == field){ //Check if field is "zero"th value in the queue
		volatilityQueue[0] = volatilityQueue[1]; //Shift value down
		volatilityQueue[1] = volatilityQueue[2]; //Shift value down
		volatilityQueue[2] = field; //Make field least volatile
	}
	else if(volatilityQueue[1] == field){ //Check if field is "one"th value in the queue
		volatilityQueue[1] = volatilityQueue[2]; //Shift value down
		volatilityQueue[2] = field; //Make field least volatile
	}
}

template<typename T>
void RightEndTriplet<T>::recalculateMostVolatile(){ //Multiplies or divides the two most recent fields and sets most volatile field
	if(volatilityQueue[0] == &a)
		a = divRightEnd(p, b, numBits);
		
	else if(volatilityQueue[0] == &b)
		b = divRightEnd(p, a, numBits);
		
	else if(volatilityQueue[0] == &p)
		p = multRightEnd(a, b, numBits);
}

template<typename T>
T RightEndTriplet<T>::powerOfTwo(int exp){
	T one = 1;
	return one << exp;
}

template<typename T>
T RightEndTriplet<T>::rightEnd(const T& num, int len){ //Returns the right end of a number
	T mask = powerOfTwo(len) - 1; //Create bit mask by taking a power of two minus one
	return num & mask; //Remove unwanted bits by ANDing the number with the bit mask
}

template<typename T>
T RightEndTriplet<T>::multRightEnd(const T& multA, const T& multB, int len){ //Returns a specified length of the right end of the product after multiplying two multiplicands
	return rightEnd(multA * multB, len); //Call rightEnd function on the product
}

template<typename T>
T RightEndTriplet<T>::divRightEnd(const T& prod, const T& mult, int len){
	if(len <= 0)
		return 0;
	
	if(prod & 1 == 0)
		throw "Attempted to divide right ends with an even product";
	
	if(mult & 1 == 0)
		throw "Attempted to divide right ends with an even multiplicand";
	
	T otherMult = 1; //Unknown multiplicand
	
	for(int i=1; i<=len; i++){ //Iterate through bits in right end
		if(multRightEnd(mult, otherMult, i) != rightEnd(prod, i)) //Check if triplet equation is satisfied to the i'th bit
			otherMult = setBit(otherMult, i); //If not, set i'th bit of otherMult to 1
	}
	
	return otherMult;
}

template<typename T>
T RightEndTriplet<T>::setBit(const T& num, int bitLocation){ //Returns the input number with the specified bit set to 1
	return num | powerOfTwo(bitLocation-1);//(T) pow(2, bitLocation-1); //OR number with a power of two to set single bit
}

#endif