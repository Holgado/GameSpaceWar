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
#include "PoligonoCSG.h"
enum Modelos {
    HERO,
    ALIEN,
    BUILD,
    HOUSE,
    BULLET
};

class Instancia {
    //Poligono *modelo;
protected:    
    MatrixDrawning* drawning;
    Modelos tipo;
    Ponto Posicao, Escala, Direcao, Velocidade;
    float rotacao;
    bool moving = false;
public:
    Ponto pontosBezier[3];

    PoligonoCSG envelope;
    Instancia() {}
    Instancia(Modelos tipo);

    void setMatrixDrawning(MatrixDrawning* _drawning);
    MatrixDrawning* getDrawning();
    Modelos getTipo();
    
    void setPosicao(Ponto);
    Ponto getPosicao();
    void setEscala(Ponto);
    Ponto getEscala();
    void setDirecao(Ponto);
    Ponto getDirecao();
    void setVelocidade(Ponto);
    Ponto getVelocidade();
    void setRotacao(float);
    float getRotacao();
    void setMoving(bool);
    bool getMoving();

    void desenhaNoPonto(Ponto pos);

    void criaEnvelope ();

    void desenha(bool);
};


#endif /* Instancia_hpp */
