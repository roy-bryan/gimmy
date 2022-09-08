class RightEndTriplet
{
private:
	int a = 1; //First multiplicand
	int b = 1; //Second multiplicand
	int p = 1; //Product
	int* volatilityQueue[3]; //Pointers to fields, showing which one should be overwritten first
	
	int numBits; //Number of bits to track
	
	void setLeastVolatile(int*); //Moves pointed field to least volatile spot
	void recalculateMostVolatile(); //Multiplies or divides the two most recent fields and sets most volatile field
	
	int multRightEnd(int, int, int len); //Multiplies numbers and returns right end of product
	int divRightEnd(int prod, int mult, int len); //Divides and returns right end of other multiplicand
	
	int rightEnd(int, int len); //Returns right end of number
	int setBit(int, int bitLocation); //Returns the input number with the specified bit set to 1
public:
	RightEndTriplet(); //Default constructor
	RightEndTriplet(int); //Constructor
	
	int getA(){ return a; }; //Getter for a
	void setA(int); //Setter for a
	int getB(){ return b; }; //Getter for b
	void setB(int); //Setter for b
	int getP(){ return p; }; //Getter for p
	void setP(int); //Setter for p
};