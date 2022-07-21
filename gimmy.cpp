#include <iostream>
#include <math.h>
#include <bitset>

using namespace std;

int numberOfBitsUsed(unsigned int);
unsigned int firstUsedBits(unsigned int, int);
unsigned int lastBits(unsigned int, int);

unsigned int generatePart(unsigned int, int, int);

unsigned int lastDiv(unsigned int p, unsigned int b, int length);
unsigned int lastProd(unsigned int a, unsigned int b, int length);

int main(int argc, char *argv[]) {
   unsigned int inputNumber = atoi(argv[1]);
   int targetLength = atoi(argv[2]);
   
   if(targetLength == 0){ //If no second argument is given, or if it is zero, hash to a 32-bit value
   	 targetLength = 32;
   }
   
   int length = numberOfBitsUsed(inputNumber); //Number of bits in input number
   
   int halfLength = (length + 1)/2; //Number of bits in each half (for integers with an odd number of bits, the middle bit is shared by both halves)
   
   //Separate number into two halves
   unsigned int firstHalf = firstUsedBits(inputNumber, halfLength); //Used to generate b
   unsigned int lastHalf = lastBits(inputNumber, halfLength); //Used to generate p
   
   //Create b and p
   unsigned int b = generatePart(firstHalf, halfLength, targetLength);
   unsigned int p = generatePart(lastHalf, halfLength, targetLength);
   
   //Make sure b and p are not equal because that makes for a boring hash value
   if(p == b){
   	b = b ^ -1;
   }
   
   unsigned int a = lastDiv(p, b, targetLength); //Hash value
   
   cout << a << endl; //Output result
   
   return 0;
}

int numberOfBitsUsed(unsigned int num){ //Takes a 32-bit number and returns the number of bits that would remain if all leading zeros were removed
   int length = 0; //Initialize length to zero
   
   while (num >= pow(2, length)) { //For each power of two that the number is greater than, increment length by 1
   	length++;
   }
   
   return length;
}

unsigned int firstUsedBits(unsigned int x, int length){ //Returns a number with only the first n bits of x (not counting leading zeros)
	int totalLength = numberOfBitsUsed(x); //Find total length without leading zeros
	
	if(length >= totalLength || length < 0) return x; //Filter out cases where n is greater than the total number of bits available or when n is negative
	
	else return x >> (totalLength - length); //Move desired bits to the right side and get rid of unwanted bits
}

unsigned int lastBits(unsigned int x, int n){ //Returns a number with only the last n bits of x
	if(n == 32) return x; //2^32 is too big to be stored in an integer, but we can just return the input number
	
	return x % (unsigned int)pow(2,n); //Remove unwanted bits by taking num modulus a power of two
}

unsigned int generatePart(unsigned int x, int xLength, int targetLength){ //Generates either b or p from x  
   unsigned int part; //Value to be returned
   
   //Handle edge cases with default values
   if(xLength > 32 || xLength < 0) xLength = 32;
   if(targetLength > 32 || targetLength < 0) targetLength = 32;
   
   unsigned int temp = x; //Copy x so we can mutilate it
   int parity = 0; //Parity bit to make an even number of 1's in x
   
   for (int i = 0; i < xLength; i++) { //Iterate through x
   	 int bit = temp & 1; //Current bit
	 parity = parity xor bit; //Flip parity bit if the current bit is a one
	 temp = temp >> 1; //Shift temp to get ready for the next bit
   }
   
   
   if(targetLength <= xLength) { //If the desired length is less than or equal to the length of x, shift the number to only have the desired number of bits
     part = x >> (xLength - targetLength);
   }
   else { //If the desired length is greater than the length of x, shift to the left to make room for the parity bit
   	 part = x << 1;
   }
   part = part & -2; //Zero the last bit to make room for the parity bit
   
   part = part + parity; //Add the parity bit to the end
   
   return part; //Return the number
}

unsigned int lastDiv(unsigned int p, unsigned int b, int length){ //Returns the last few bits of the number, a, which multiplies with b to get a product with the same last few digits of the number p
	unsigned int a = 0; //Divisor a
	
	for(int i=1; i<=length; i++){ //Start by solving for the last bit of a, then the last two, and so on until all the bits of a that we care about are known
		if(lastProd(a, b, i) != lastBits(p, i)) //Compare the last few bits of the product of a and b with the last few bits of p to see if they match
			a += pow(2, i-1); //If not, we know that the last i-1 bits of a are correct, so the i-th to last bit must be incorrect; we set it to a one because it started as a zero
	}
	
	return a; //Now that we have solved for all the digits we care about, return a
}

unsigned int lastProd(unsigned int a, unsigned int b, int length){ //Appends a 1 to the end of each number, then multiplies them and returns the product shifted right
	unsigned long divA = (a << 1) + 1; //Append 1 to the end of a
	unsigned long divB = (b << 1) + 1; //Append 1 to the end of b
	unsigned long product = divA*divB; //Multiply a and b to find the product
	
	product = product >> 1; //Remove the last bit from the product
	
	return lastBits((unsigned int)product, length); //Return only the requested number of bits from the product
}