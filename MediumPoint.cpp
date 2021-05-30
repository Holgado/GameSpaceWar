//
//  Ponto.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 18/08/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#include "MediumPoint.h"

MediumPoint::MediumPoint (){

}

MediumPoint::MediumPoint(Ponto startPoint,Ponto finalPoint){
	this->startPoint = startPoint;
	this->finalPoint = finalPoint;

	this->mediumPoint.x = (startPoint.x + finalPoint.x) /2;
	this->mediumPoint.y = (startPoint.y + finalPoint.y) /2;
}

bool MediumPoint::getState(){
	return state;
}

void MediumPoint::setState(bool newstate){
	state = newstate;
}

Ponto MediumPoint::getMediumPoint(){
	return mediumPoint;
}

Ponto MediumPoint::getStartPoint(){
	return startPoint;
}

Ponto MediumPoint::getFinalPoint(){
	return finalPoint;
}

bool MediumPoint::getAlreadVisited(){
	return this->alreadVisited;
}
void MediumPoint::setAlreadVisited(bool visited){
	this->alreadVisited = visited;
}

/*
void MediumPoint::setStartPoint(Ponto startPoint){
	this.startPoint = startPoint;
}

void MediumPoint::setFinalPoint(Ponto finalPoint){
	this.finalPoint = finalPoint;
}

void MediumPoint::CalcMediumPoint(){
	this.MediumPoint.x = (startPoint.x + finalPoint.x) /2;
	this.MediumPoint.y = (startPoint.y + finalPoint.y) /2;
}*/
