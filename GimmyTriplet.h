#ifndef GIMMY_TRIPLET
#define GIMMY_TRIPLET

#include "RightEndTriplet.cpp"

class GimmyTriplet
{
private:
	RightEndTriplet* triplet; //Mathematical triplet
	
public:
	GimmyTriplet(); //Default constructor
	GimmyTriplet(int); //Constructor
	
	int getA(){ return triplet->getA() >> 1; }; //Pass through getter for A
	void setA(int num){ triplet->setA((num << 1) + 1); }; //Pass through setter for A
	int getB(){ return triplet->getB() >> 1; }; //Pass through getter for B
	void setB(int num){ triplet->setB((num << 1) + 1); }; //Pass through setter for B
	int getP(){ return triplet->getP() >> 1; }; //Pass through getter for P
	void setP(int num){ triplet->setP((num << 1) + 1); }; //Pass through setter for P
};

GimmyTriplet::GimmyTriplet(){ //Default constructor
	GimmyTriplet(32);
}

GimmyTriplet::GimmyTriplet(int numBits){ //Constructor
	triplet = new RightEndTriplet(numBits + 1);
}

#endif