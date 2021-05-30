#include "PoligonoCSG.h"

PoligonoCSG::PoligonoCSG() {}

Poligono PoligonoCSG::QuebraPoligono(Poligono A, Poligono B)
{
    int i_a = 0, j_a = 0;
    Ponto p1, p2;
    Poligono P;
    int intersec;

    for (unsigned long i = 0; i < A.getNVertices(); i++)
    {
        i_a = verificaFinal(i, A.getNVertices());
        for (unsigned long j = 0; j < B.getNVertices(); j++)
        {
            j_a = verificaFinal(j, B.getNVertices());
            intersec = GetPontosInteresec(A.getVertice(i), A.getVertice(i_a), B.getVertice(j), B.getVertice(j_a), p1, p2); // Calcula a intersec

            if (intersec == 1)
            {
                P.insereVertice(A.getVertice(i)); // A
                P.insereVertice(p1);              // Adiciona na lista
            }
            else
            {
                P.insereVertice(A.getVertice(i)); // Verificar se ja existe antes de adicionar
            }
        }
    }
    return P;
}

bool PoligonoCSG::hasCollision(Ponto theInitial, Ponto theFinal, Ponto mediumPoint)
{
    Ponto xmin = Ponto(mediumPoint.x - 1000, mediumPoint.y, 0);

    if (HaInterseccao(theInitial, theFinal, xmin, mediumPoint))
    {
        return true;
    }
    return false;
}

bool PoligonoCSG::isInside(Ponto mediumPoint, Poligono toVerify)
{
    int cont = 0, i_1;
    for (unsigned long i = 0; i < toVerify.getNVertices(); i++)
    {
        i_1 = verificaFinal(i, toVerify.getNVertices());
        if (hasCollision(toVerify.getVertice(i), toVerify.getVertice(i_1), mediumPoint))
        {
            cont++;
        }
    }

    if (cont % 2 == 0)
    {
        return false; // se for par o ponto esta fora
    }
    return true; // se for impar o ponto esta detro.
}

vector<MediumPoint> PoligonoCSG::returnMediumPoints(Poligono BrokenPoligon)
{
    int i_1 = 0;
    vector<MediumPoint> mediumPoints;

    for (int i = 0; i < BrokenPoligon.getNVertices(); i++)
    {
        i_1 = verificaFinal(i, BrokenPoligon.getNVertices());
        mediumPoints.push_back(MediumPoint(BrokenPoligon.getVertice(i), BrokenPoligon.getVertice(i_1)));
    }
    return mediumPoints;
}

void PoligonoCSG::ClassifyState(vector<MediumPoint> &mediumPoint, Poligono BrokenPoligon)
{
    for (int i = 0; i < mediumPoint.size(); i++)
    {
        if (isInside(mediumPoint.at(i).getMediumPoint(), BrokenPoligon))
        {
            mediumPoint.at(i).setState(true);
        }
        else
        {
            mediumPoint.at(i).setState(false);
        }
    }
}

Ponto PoligonoCSG::FIndThFirstPoint(vector<MediumPoint> mediumPointA, bool inOrOut){
	for(int i=0; i < mediumPointA.size(); i++){
		if(mediumPointA.at(i).getState() == inOrOut){
			return 	mediumPointA.at(i).getStartPoint();
		}
	}
	return mediumPointA.at(0).getStartPoint();
}

int PoligonoCSG::howManyPointsToBeIncludes(vector<MediumPoint> mediumPointA, bool inOrOut){
	int cont =0;

	for(int i=0; i < mediumPointA.size(); i++){
		if(mediumPointA.at(i).getState() == inOrOut){
			cont++;
		}
	}
	return cont;
}

int PoligonoCSG::ReturnThePositionIfExists(vector<MediumPoint> mediumPointA, Ponto startPoint){
	for(int i=0; i < mediumPointA.size(); i++){
		if(isPontoEqual(mediumPointA.at(i).getStartPoint(), startPoint) && (mediumPointA.at(i).getAlreadVisited() == false)){
			return i;
		}
	}
	return 0;

}

int PoligonoCSG::ReturnThePositionIfExistsFinal(vector<MediumPoint> mediumPointA, Ponto finalPoint){
	for(int i=0; i < mediumPointA.size(); i++){
		if(isPontoEqual(mediumPointA.at(i).getFinalPoint(), finalPoint) && (mediumPointA.at(i).getAlreadVisited() == false)){
			return i;
		}
	}
	return 0;

}

bool PoligonoCSG::isPontoEqual(Ponto A, Ponto B) {
    if (A.x == B.x && A.y == B.y) {
        return true;
    }
    return false;
}

////////////////////////////// Search and add Methods ////////////////////////////

Ponto PoligonoCSG::ReturnPositionAfterIncludeInTheList(vector<MediumPoint> vectorToAnalyzes, int &cont, bool getTheInside, Poligono &Union,Ponto PointToFind)
{	
	int position;

	position = ReturnThePositionIfExists(vectorToAnalyzes,PointToFind);
	while (cont >= 0)
    {
			if(getTheInside){
        		if (vectorToAnalyzes.at(position).getState()){	
            		Union.insereVertice(vectorToAnalyzes.at(position).getStartPoint());
                	Union.insereVertice(vectorToAnalyzes.at(position).getFinalPoint());
					position = ReturnThePositionIfExists(vectorToAnalyzes,vectorToAnalyzes.at(position).getFinalPoint());
					vectorToAnalyzes.at(position).setAlreadVisited(true);
                	cont--;
            	}else{
				
					cont--;
					break;
				}
			}else{
				if (!vectorToAnalyzes.at(position).getState()){
            		Union.insereVertice(vectorToAnalyzes.at(position).getStartPoint());
            	    Union.insereVertice(vectorToAnalyzes.at(position).getFinalPoint());
					position = ReturnThePositionIfExists(vectorToAnalyzes,vectorToAnalyzes.at(position).getFinalPoint());
					vectorToAnalyzes.at(position).setAlreadVisited(true);
            	    cont--;
            	}else{
					cont--;
					break;
				}
			}	
		}
	return vectorToAnalyzes.at(position).getStartPoint();
}

Ponto PoligonoCSG::ReturnPositionAfterIncludeInTheListReverse(vector<MediumPoint> vectorToAnalyzes, int &cont, bool getTheInside, Poligono &Union,Ponto PointToFind)
{	
	int position;

	position = ReturnThePositionIfExistsFinal(vectorToAnalyzes,PointToFind);
	while (cont >= 0)
    {
			if(getTheInside){
        		if (vectorToAnalyzes.at(position).getState()){
					Union.insereVertice(vectorToAnalyzes.at(position).getFinalPoint());
            		Union.insereVertice(vectorToAnalyzes.at(position).getStartPoint());                	
					position = ReturnThePositionIfExistsFinal(vectorToAnalyzes,vectorToAnalyzes.at(position).getStartPoint());
					vectorToAnalyzes.at(position).setAlreadVisited(true);
                	cont--;
            	}else{
				
					cont--;
					break;
				}
			}else{
				if (!vectorToAnalyzes.at(position).getState()){				
            	    Union.insereVertice(vectorToAnalyzes.at(position).getFinalPoint());
            		Union.insereVertice(vectorToAnalyzes.at(position).getStartPoint());
					position = ReturnThePositionIfExistsFinal(vectorToAnalyzes,vectorToAnalyzes.at(position).getStartPoint());
					vectorToAnalyzes.at(position).setAlreadVisited(true);
            	    cont--;
            	}else{
					cont--;
					break;
				}
			}	

	}
	return vectorToAnalyzes.at(position).getFinalPoint();
}

/////////////////////////// Boleans Methods //////////////////////////////////////////


void PoligonoCSG::AddToUniaoPoligon(vector<MediumPoint> mediumPointA, vector<MediumPoint> mediumPointB, Poligono &Union)
{
    bool ADone = false, BDone = false, TaskDone = false;
	int actualPositionVectorA = 0, actualPositionVectorB = 0,ContA=0, ContB=0 ;
	Ponto PointAToFind, PointBToFind;

	PointAToFind = FIndThFirstPoint(mediumPointA, false); // True to gets inside Points False Gets the Out Points
	ContA = howManyPointsToBeIncludes(mediumPointA, false);
	ContB = howManyPointsToBeIncludes(mediumPointB, false);
	while(!TaskDone){
		if(!ADone){ 
			PointBToFind = ReturnPositionAfterIncludeInTheList(mediumPointA, ContA, false, Union, PointAToFind);
			if(ContA <= 0) { ADone = true; }
		}
		if(!BDone){
			PointAToFind = ReturnPositionAfterIncludeInTheList(mediumPointB, ContB, false, Union, PointBToFind);	
			if(ContB <= 0) { BDone = true; }
		}
		if(ADone == true && BDone == true){ TaskDone = true; }
	}
}

void PoligonoCSG::AddToIntersectionPoligon(vector<MediumPoint> mediumPointA, vector<MediumPoint> mediumPointB, Poligono &Intersection)
{
	bool ADone = false, BDone = false, TaskDone = false;
	int actualPositionVectorA = 0, actualPositionVectorB = 0,ContA=0, ContB=0 ;
	Ponto PointAToFind, PointBToFind;

	PointAToFind = FIndThFirstPoint(mediumPointA, true); // True to gets inside Points False Gets the Out Points
	ContA = howManyPointsToBeIncludes(mediumPointA, true);
	ContB = howManyPointsToBeIncludes(mediumPointB, true);

	while(!TaskDone){
		if(!ADone){ 
			PointBToFind = ReturnPositionAfterIncludeInTheList(mediumPointA, ContA, true, Intersection, PointAToFind);
			if(ContA <= 0) { ADone = true; }
		}
		if(!BDone){
			PointAToFind = ReturnPositionAfterIncludeInTheList(mediumPointB, ContB, true, Intersection, PointBToFind);	
			if(ContB <= 0) { BDone = true; }
		}
		if(ADone == true && BDone == true){ TaskDone = true; }
	}
}

void PoligonoCSG::AddToABPoligon(vector<MediumPoint> mediumPointA, vector<MediumPoint> mediumPointB, Poligono &AB)
{
	bool ADone = false, BDone = false, TaskDone = false;
	int actualPositionVectorA = 0, actualPositionVectorB = 0,ContA=0, ContB=0 ;
	Ponto PointAToFind, PointBToFind;
	PointAToFind = FIndThFirstPoint(mediumPointA, false); // True to gets inside Points False Gets the Out Points
	ContA = howManyPointsToBeIncludes(mediumPointA, false);
	ContB = howManyPointsToBeIncludes(mediumPointB, true);
	
	while(!TaskDone){
		if(!ADone){ 
			PointBToFind = ReturnPositionAfterIncludeInTheList(mediumPointA, ContA, true, AB, PointAToFind);
			if(ContA <= 0) { ADone = true; }
		}
		if(!BDone){
			PointAToFind = ReturnPositionAfterIncludeInTheListReverse(mediumPointB, ContB, false, AB, PointBToFind);	
			if(ContB <= 0) { BDone = true; }
		}
		if(ADone == true && BDone == true){ TaskDone = true; }
	}
}

void PoligonoCSG::AddToBAPoligon(vector<MediumPoint> mediumPointA, vector<MediumPoint> mediumPointB, Poligono &BA)
{
	bool ADone = false, BDone = false, TaskDone = false;
	int actualPositionVectorA = 0, actualPositionVectorB = 0,ContA=0, ContB=0 ;
	Ponto PointAToFind, PointBToFind;

	PointBToFind = FIndThFirstPoint(mediumPointB, true); // True to gets inside Points False Gets the Out Points
	ContA = howManyPointsToBeIncludes(mediumPointA, false);
	ContB = howManyPointsToBeIncludes(mediumPointB, true);
	while(!TaskDone){
		if(!BDone){
			PointAToFind = ReturnPositionAfterIncludeInTheListReverse(mediumPointB, ContB, true, BA, PointBToFind);	
			if(ContB <= 0) { BDone = true; }
		}
		if(!ADone){ 
			PointBToFind = ReturnPositionAfterIncludeInTheList(mediumPointA, ContA, false, BA, PointAToFind);
			if(ContA <= 0) { ADone = true; }
		}
		
		if(ADone == true && BDone == true){ TaskDone = true; }
	}
}
/********************* Public Methods ***********************/
/************************************************************/
Poligono PoligonoCSG::CalculaUniao(Poligono A, Poligono B)
{
    Poligono Union;

    Poligono BrokenPoligonA = QuebraPoligono(A, B);
    Poligono BrokenPoligonB = QuebraPoligono(B, A);

    vector<MediumPoint> mediumPointPoligonA = returnMediumPoints(BrokenPoligonA);
    vector<MediumPoint> mediumPointPoligonB = returnMediumPoints(BrokenPoligonB);

    ClassifyState(mediumPointPoligonA, B);
    ClassifyState(mediumPointPoligonB, A);

    AddToUniaoPoligon(mediumPointPoligonA, mediumPointPoligonB, Union);

    return Union;
}

Poligono PoligonoCSG::CalculaInter(Poligono A, Poligono B)
{
    Poligono Intersection;
    Poligono BrokenPoligonA = QuebraPoligono(A, B);
    Poligono BrokenPoligonB = QuebraPoligono(B, A);

    vector<MediumPoint> mediumPointPoligonA = returnMediumPoints(BrokenPoligonA);
    vector<MediumPoint> mediumPointPoligonB = returnMediumPoints(BrokenPoligonB);

    ClassifyState(mediumPointPoligonA, B);
    ClassifyState(mediumPointPoligonB, A);

    AddToIntersectionPoligon(mediumPointPoligonA, mediumPointPoligonB, Intersection);

    return Intersection;
}

Poligono PoligonoCSG::CalculaAB(Poligono A, Poligono B)
{
    Poligono AB;

    Poligono BrokenPoligonA = QuebraPoligono(A, B);
    Poligono BrokenPoligonB = QuebraPoligono(B, A);

    vector<MediumPoint> mediumPointPoligonA = returnMediumPoints(BrokenPoligonA);
    vector<MediumPoint> mediumPointPoligonB = returnMediumPoints(BrokenPoligonB);

    ClassifyState(mediumPointPoligonA, B);
    ClassifyState(mediumPointPoligonB, A);

    AddToABPoligon(mediumPointPoligonA,mediumPointPoligonB, AB);

    return AB;
}

Poligono PoligonoCSG::CalculaBA(Poligono A, Poligono B)
{
    Poligono BA;

    Poligono BrokenPoligonA = QuebraPoligono(A, B);
    Poligono BrokenPoligonB = QuebraPoligono(B, A);

    vector<MediumPoint> mediumPointPoligonA = returnMediumPoints(BrokenPoligonA);
    vector<MediumPoint> mediumPointPoligonB = returnMediumPoints(BrokenPoligonB);

    ClassifyState(mediumPointPoligonA, B);
    ClassifyState(mediumPointPoligonB, A);

    AddToBAPoligon(mediumPointPoligonA, mediumPointPoligonB, BA);
	
    return BA;
}
int PoligonoCSG::verificaFinal(int i, int tam)
{
    int isum;
    if ((i + 1) < tam)
    {
        isum = i + 1;
    }
    else
    {
        isum = 0;
    }
    return isum;
}
