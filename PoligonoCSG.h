//
//  PoligonoCSG.cpp
//  Operacoes booleanas com Poligonos
//
//  Created by Marcelo Holgado e Nicolas Moura on 18/03/21.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#ifndef PoligonoCSG_hpp
#define PoligonoCSG_hpp

#include <iostream>
using namespace std;


#ifdef WIN32
#include <windows.h>
#include <glut.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

#include "Poligono.h"
#include "Ponto.h"
#include <vector>
#include "MediumPoint.h"

class PoligonoCSG : public Poligono
{
private:
    vector<Ponto> ptnsIntersec; //lista de pontos de interc
    int verificaFinal(int i, int tam);
    Poligono QuebraPoligono(Poligono A, Poligono B);
    vector<Ponto> VerificaInclusao(Poligono A1, Poligono B1);
	Ponto mediumPoint(Ponto, Ponto);
	bool hasCollision(Ponto, Ponto, Ponto);
	
	void ClassifyState(vector<MediumPoint> &mediumPoint,Poligono BrokenPoligon);
	vector<MediumPoint> returnMediumPoints(Poligono BrokenPoligon);
	void AddToUniaoPoligon(vector<MediumPoint> mediumPointPoligonA,vector<MediumPoint> mediumPointPoligonB,Poligono &Union);
	void AddToIntersectionPoligon(vector<MediumPoint> mediumPointA,vector<MediumPoint> mediumPointB,Poligono &Intersection);
    void AddToABPoligon(vector<MediumPoint> mediumPointA,vector<MediumPoint> mediumPointB,Poligono &Intersection);
    void AddToBAPoligon(vector<MediumPoint> mediumPointA,vector<MediumPoint> mediumPointB,Poligono &Intersection);
	Ponto ReturnPositionAfterIncludeInTheList(vector<MediumPoint> vectorToAnalyzes, int &cont, bool getTheInside, Poligono &vector,Ponto PointToFind);
    Ponto ReturnPositionAfterIncludeInTheListReverse(vector<MediumPoint> vectorToAnalyzes, int &cont, bool getTheInside, Poligono &vector,Ponto PointToFind);
	bool isPontoEqual(Ponto A, Ponto B);
	int ReturnThePositionIfExists(vector<MediumPoint> mediumPointA, Ponto startPoint);
	Ponto FIndThFirstPoint(vector<MediumPoint> mediumPointA, bool inOrOut);
	int howManyPointsToBeIncludes(vector<MediumPoint> mediumPointA, bool inOrOut);
	int ReturnThePositionIfExistsFinal(vector<MediumPoint> mediumPointA, Ponto startPoint);
public:
    PoligonoCSG();
	bool isInside(Ponto, Poligono);
    Poligono CalculaUniao(Poligono A, Poligono B);
    Poligono CalculaInter(Poligono A, Poligono B);
    Poligono CalculaAB(Poligono A, Poligono B);
    Poligono CalculaBA(Poligono A, Poligono B);
};
#endif 
