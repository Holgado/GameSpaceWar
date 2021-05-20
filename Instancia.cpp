//
//  Instancia.cpp
//  OpenGLTest
//
//  Created by Márcio Sarroglia Pinho on 22/09/20.
//  Copyright © 2020 Márcio Sarroglia Pinho. All rights reserved.
//

#include "Instancia.h"


void DesenhaPersonagem();
void DesenhaRetangulo();
void InstanciaPonto(Ponto &p, Ponto &out);
Ponto InstanciaPonto(Ponto P);

Instancia::Instancia(Modelos _tipo) {
    tipo = _tipo;
}

/*****************************************************************/
// Geters and Seters
void Instancia::setMatrixDrawning(MatrixDrawning* _drawning) {
    this->drawning = _drawning;
}

MatrixDrawning* Instancia::getDrawning() {
    return drawning;
}

Modelos Instancia::getTipo(){
    return tipo;
}
    
void Instancia::setPosicao(Ponto posicao) {
    Posicao = posicao;
}
Ponto Instancia::getPosicao() {
    return Posicao;
}
void Instancia::setEscala(Ponto escala) {
    Escala = escala;
}
Ponto Instancia::getEscala() {
    return Escala;
}
void Instancia::setDirecao(Ponto direcao) {
    Direcao = direcao;
}
Ponto Instancia::getDirecao() {
    return Direcao;
}
void Instancia::setVelocidade(Ponto velocidade) {
    Velocidade = velocidade;
}
Ponto Instancia::getVelocidade() {
    return Velocidade;
}
void Instancia::setRotacao(float _rotacao) {
    rotacao = _rotacao;
}
float Instancia::getRotacao() {
    return rotacao;
}
/*****************************************************************/
// Draw functions
void Instancia::desenha()
{
    // aplica as transformacoes geometricas no modelo
    // desenha a geometria do objeto
    
    glPushMatrix();
    glTranslatef(Posicao.x, Posicao.y, 0);
    glRotatef(rotacao, 0, 0, 1);
    
    if (tipo == ALIEN || tipo == HERO) {
        glScalef(0.5, 0.5, 0);
    }
    else {
        glScalef(1.5, 1.5, 0);
    }
    
    Ponto PosicaoDoPersonagem;
    Ponto Origem (0,0,0);
    InstanciaPonto(Origem, PosicaoDoPersonagem);
    //PosicaoDoPersonagem.imprime(); cout << endl;
    drawning->drawModel(PosicaoDoPersonagem);
    //DesenhaPersonagem();
    glPopMatrix();
}

// ***********************************************************
//  void InstanciaPonto(Ponto3D *p, Ponto3D *out)
//  Esta funcao calcula as coordenadas de um ponto no
//  sistema de referencia do universo (SRU), ou seja,
//  aplica as rotacoes, escalas e translacoes a um
//  ponto no sistema de referencia do objeto (SRO).
// ***********************************************************
void InstanciaPonto(Ponto &p, Ponto &out)
{
    GLfloat ponto_novo[4];
    GLfloat matriz_gl[4][4];
    int  i;
    
    glGetFloatv(GL_MODELVIEW_MATRIX,&matriz_gl[0][0]);
    
    for(i=0;i<4;i++)
    {
        ponto_novo[i]= matriz_gl[0][i] * p.x+
        matriz_gl[1][i] * p.y+
        matriz_gl[2][i] * p.z+
        matriz_gl[3][i];
    }
    out.x=ponto_novo[0];
    out.y=ponto_novo[1];
    out.z=ponto_novo[2];
}

Ponto InstanciaPonto(Ponto P)
{
    Ponto temp;
    InstanciaPonto(P, temp);
    return temp;
}

