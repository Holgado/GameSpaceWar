//
//  Instancia.h
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 22/09/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//


#ifndef Instancia_hpp
#define Instancia_hpp
#include <iostream>
using namespace std;

#include "matrixdrawning.h"
#include "Ponto.h"

class Instancia {
    //Poligono *modelo;
private:    
    MatrixDrawning drawning;
public:
    Ponto Posicao, Escala, Direcao, Velocidade;
    float rotacao;
    int modelo;     // 1 = hero // 2 = alien // 3 = building // 4 = house
    void setMatrixDrawning(MatrixDrawning _drawning);
    MatrixDrawning getDrawning();
    void desenha();
};


#endif /* Instancia_hpp */
