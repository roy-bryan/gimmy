#ifndef GIMMY_TRIPLET
#define GIMMY_TRIPLET

#include "RightEndTriplet.cpp"

template<typename T>
class GimmyTriplet
{
private:
	RightEndTriplet<T>* triplet; //Mathematical triplet
	
public:
	GimmyTriplet(); //Default constructor
	GimmyTriplet(int); //Constructor
	
	T getA(){ return triplet->getA() >> 1; }; //Pass through getter for A
	void setA(T num){ triplet->setA((num << 1) + 1); }; //Pass through setter for A
	T getB(){ return triplet->getB() >> 1; }; //Pass through getter for B
	void setB(T num){ triplet->setB((num << 1) + 1); }; //Pass through setter for B
	T getP(){ return triplet->getP() >> 1; }; //Pass through getter for P
	void setP(T num){ triplet->setP((num << 1) + 1); }; //Pass through setter for P
};

template<typename T>
GimmyTriplet<T>::GimmyTriplet(){ //Default constructor
	GimmyTriplet(32);
}

template<typename T>
GimmyTriplet<T>::GimmyTriplet(int numBits){ //Constructor
	triplet = new RightEndTriplet<T>(numBits + 1);
}

#endif