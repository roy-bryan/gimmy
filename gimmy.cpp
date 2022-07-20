#include <iostream>
#include <math.h>
#include <bitset>

using namespace std;

unsigned int lastBits(unsigned int, int);
unsigned int lastDiv(unsigned int p, unsigned int b, int length);
unsigned int lastProd(unsigned int a, unsigned int b, int length);

int main(int argc, char *argv[]) {
   unsigned int num1 = atoi(argv[1]);
   int lengthb = atoi(argv[2]);
   
   if(lengthb == 0){ //If no second argument is given, or if it is zero, hash to a 32-bit value
   	 lengthb = 32;
   }
   
   int length = 0;
   while (num1 >= pow(2, length)) {
   	length++;
   }
   
   int hflength = length + 1;
   hflength = hflength / 2;
   
   
   unsigned int lasthf = num1 & (int)round(pow(2, hflength) - 1);
   unsigned int firsthf = num1 >> (length / 2);
   
   unsigned int b = 0;
   unsigned int temp = firsthf;
   
   for (int i = 0; i < hflength; i++) {
   	 int bit = temp & 1;
	 b = b xor bit;
	 temp = temp >> 1;
   }
   
   
   
   if(lengthb <= hflength) {
     firsthf = firsthf >> (hflength - lengthb);
   }
   else {
   	 firsthf = firsthf << 1;
   }
   
   firsthf = firsthf & -2;
   b = b + firsthf;
   
   
   
   
   
   unsigned int p = 0;
   temp = lasthf;
   
   for (int i = 0; i < hflength; i++) {
   	 int bit = temp & 1;
	 p = p xor bit;
	 temp = temp >> 1;
   }

   
   
   if(lengthb <= hflength) {
     lasthf = lasthf >> (hflength - lengthb);
   }
   else {
   	 lasthf = lasthf << 1;
   }
   
   lasthf = lasthf & -2;
   p = p + lasthf;
   
   unsigned int a = lastDiv(p, b, lengthb);
   
   cout << a << endl;
   
   return 0;
}

unsigned int lastBits(unsigned int num, int length){ //Returns a number with only the last few bits of the num (the number of bits in the returned number is determined by the length argument)
	if(length == 32) return num; //2^32 is too big to be stored in an integer, but we can just return the input number
	
	return num % (unsigned int)pow(2,length); //Remove unwanted bits by taking num modulus a power of two
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