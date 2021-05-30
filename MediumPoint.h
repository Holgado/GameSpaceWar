#ifndef MediumPoint_hpp
#define MediumPoint_hpp

#include <iostream>
#include "Ponto.h"

using namespace std;

class MediumPoint{
    
private:
	bool state;				//True dentro False fora
	Ponto mediumPoint;
	Ponto startPoint;
	Ponto finalPoint;
	bool alreadVisited;
public:
	MediumPoint ();
	MediumPoint(Ponto startPoint,Ponto finalPoint);
	bool getState();
	void setState(bool newstate);
	Ponto getMediumPoint();
	Ponto getStartPoint();
	Ponto getFinalPoint();
	bool getAlreadVisited();
	void setAlreadVisited(bool visited);
	//void setStartPoint(Ponto startPoint);
	//void setFinalPoint(Ponto finalPoint);
	//void CalcMediumPoint();
};

#endif

