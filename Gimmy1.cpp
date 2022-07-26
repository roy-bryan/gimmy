#ifndef GIMMY1
#define GIMMY1

#include "Gimmy1.h"

template<typename T>
Gimmy1<T>::Gimmy1(int outputBits){
	outBits = outputBits;
	triplet = new GimmyTriplet<T>(outputBits);
}

template<typename T>
T Gimmy1<T>::hash(const T& inputNumber){
	int length = numberOfBitsUsed(inputNumber); //Number of bits in input number
	int lengthBitP = length & 1; //If the length is odd, set p's length bit to 1 and vise versa
	lengthBitP = lengthBitP << 1; //The length bit will be the second to last bit, so it should be shifted left
	int lengthBitB = lengthBitP ^ 2; //b's length bit will be the opposite of p's. We can get this by XORing with ...00010 (2)
	
	int halfLength = (length + 1)/2; //Number of bits in each half (for integers with an odd number of bits, the middle bit is shared by both halves)
	
	//Separate number into two halves
	T firstHalf = firstUsedBits(inputNumber, halfLength); //Used to generate b
	T lastHalf = lastBits(inputNumber, halfLength); //Used to generate p
	
	//Create b and p
	T b = generatePart(firstHalf, halfLength, outBits) + lengthBitB;
	T p = generatePart(lastHalf, halfLength, outBits) + lengthBitP;
	
	triplet->setB(b);
	triplet->setP(p);
	
	T a = triplet->getA(); //Hash value
	
	return a; //Return result
}

template<typename T>
int Gimmy1<T>::numberOfBitsUsed(const T& num){ //Takes a 32-bit number and returns the number of bits that would remain if all leading zeros were removed
	int length = 0; //Initialize length to zero
	
	while (num >= pow(2, length)) { //For each power of two that the number is greater than, increment length by 1
		length++;
	}
	
	return length;
}

template<typename T>
T Gimmy1<T>::firstUsedBits(const T& x, int length){ //Returns a number with only the first n bits of x (not counting leading zeros)
	int totalLength = numberOfBitsUsed(x); //Find total length without leading zeros
	
	if(length >= totalLength || length < 0) return x; //Filter out cases where n is greater than the total number of bits available or when n is negative
	
	else return x >> (totalLength - length); //Move desired bits to the right side and get rid of unwanted bits
}

template<typename T>
T Gimmy1<T>::lastBits(const T& x, int n){ //Returns a number with only the last n bits of x
	return x % (T)pow(2,n); //Remove unwanted bits by taking num modulus a power of two
}

template<typename T>
T Gimmy1<T>::generatePart(const T& x, int xLength, int targetLength){ //Generates either b or p from x, leaving the second to last bit blank (0)
	T part; //Value to be returned
	
	//Handle edge cases with default values
	if(xLength > 32 || xLength < 0) xLength = 32;
	if(targetLength > 32 || targetLength < 0) targetLength = 32;
	
	T temp = x; //Copy x so we can mutilate it
	int parity = 0; //Parity bit to make an even number of 1's in x
	
	for (int i = 0; i < xLength; i++) { //Iterate through x
		int bit = temp & 1; //Current bit
		parity = parity ^ bit; //Flip parity bit if the current bit is a one
		temp = temp >> 1; //Shift temp to get ready for the next bit
	}
	
	if(targetLength <= xLength) { //If the desired length is less than or equal to the length of x, shift the number to only have the desired number of bits
		part = x >> (xLength - targetLength);
	}
	else if(targetLength = xLength+1) { //If the desired length is greater than the length of x by one bit, shift to the left by one to achieve desired length
		part = x << 1;
	}
	else {
		part = x << 2; //If the desired length is greater than the length of x by more than one bit, shift to the left to make room for the length bit and the parity bit
	}
	part = part & -4; //Zero the last 2 bits to make room for the length bit and parity bit
	
	part = part | parity; //Add the parity bit to the end
	
	return part; //Return the number
}

#endif