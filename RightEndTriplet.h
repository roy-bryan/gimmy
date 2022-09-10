template<typename T>
class RightEndTriplet
{
private:
	T a = 1; //First multiplicand
	T b = 1; //Second multiplicand
	T p = 1; //Product
	T* volatilityQueue[3]; //Pointers to fields, showing which one should be overwritten first
	
	int numBits; //Number of bits to track
	
	void setLeastVolatile(T*); //Moves pointed field to least volatile spot
	void recalculateMostVolatile(); //Multiplies or divides the two most recent fields and sets most volatile field
	
	T multRightEnd(T, T, int len); //Multiplies numbers and returns right end of product
	T divRightEnd(T prod, T mult, int len); //Divides and returns right end of other multiplicand
	
	T rightEnd(T, int len); //Returns right end of number
	T setBit(T, int bitLocation); //Returns the input number with the specified bit set to 1
public:
	RightEndTriplet(); //Default constructor
	RightEndTriplet(int); //Constructor
	
	T getA(){ return a; }; //Getter for a
	void setA(T); //Setter for a
	T getB(){ return b; }; //Getter for b
	void setB(T); //Setter for b
	T getP(){ return p; }; //Getter for p
	void setP(T); //Setter for p
};