// **********************************************************************
// PUCRS/Escola Politecnica
// COMPUTACAO GRAFICA
//
// **********************************************************************

// Para uso no Xcode:
// Abra o menu Product -> Scheme -> Edit Scheme -> Use custom working directory
// Selecione a pasta onde voce descompactou o ZIP que continha este arquivo.
//

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

#ifdef WIN32
#include <windows.h>
#include <glut.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/glut.h>
#endif

// Includes
#include "Temporizador.h"
#include "matrixdrawning.h"
#include "Instancia.h"
#include "spaceship.h"
#include "SOIL/SOIL.h"
#include "TextureClass.h"
// Definitions
#define NUM_ALIENS 10
#define NUM_BUILDINGS 4
#define NUM_HOUSES 3
#define WIDTH 100
#define HEIGTH 100

Temporizador Timer;
MatrixDrawning *matrixDrawHero = new MatrixDrawning();
MatrixDrawning *matrixDrawAlien = new MatrixDrawning();
MatrixDrawning *matrixDrawBuilding = new MatrixDrawning();
MatrixDrawning *matrixDrawHouse = new MatrixDrawning();
MatrixDrawning *matrixDrawBullet = new MatrixDrawning();

Instancia building[NUM_BUILDINGS];
Instancia house[NUM_HOUSES];
SpaceShip alienSpaceships[NUM_ALIENS];
SpaceShip heroSpaceship;
Instancia bullet;
Instancia alienBullet[NUM_ALIENS];

GLuint BackTex;
Ponto Max, Min;

int tempo = 5;
bool startgame = false;
float TempoDaAnimacao;
bool way = false;
GLfloat AspectRatio, AngY=0;
bool shotFlag = false;
int shotIndex = rand() % 5;

// **********************************************************************
//  Functions
// **********************************************************************
void DrawAllTheCity();
void DefinesBezierCurves(bool);
void AnimateAlienShots (double dt, int index);
void detectaColisoesNoMapa();


void initBackGroundTex (void) {
    BackTex = LoadTexture("background.jpg");
}
void PosicUser()
{
	// Set the clipping volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,AspectRatio,0.01,200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0, 0, 0,-8, 0.0f, 1.0f, 0.0f);

}
Ponto CalculaBezier3(Ponto PC[], double t)
{
    Ponto P;
    double UmMenosT = 1-t;
    
    P =  PC[0] * UmMenosT * UmMenosT + PC[1] * 2 * UmMenosT * t + PC[2] * t*t;
    return P;
}

void detectaColisoes() {
    for (int i = 0; i < NUM_ALIENS; i++) {
        if (alienBullet[i].getMoving()) {
            if (bullet.envelope.isInside(alienSpaceships[i].getPosicao(), bullet.envelope) ) {
                alienSpaceships[i].setMoving(false);
                bullet.setPosicao(heroSpaceship.getPosicao());
                bullet.setMoving(false);
            }
        }
    }
}

void detectaColisoesNoMapa () {
    for(int i = 0;i < NUM_BUILDINGS; i++) {
        if (building[i].envelope.isInside(alienBullet[shotIndex].getPosicao(), building[i].envelope)) {
            building[i].setMoving(false);
        }
    }
}   

void shotBullet() {
    bullet.desenha(false);
}

void AvancaComBezier()
{
    double t;
    t = TempoDaAnimacao/tempo;
    Ponto pontosBz[3];
    if (t > 1.0) {
        DefinesBezierCurves(way);
        TempoDaAnimacao = 0;
        way = !way;
    }

    for (int i = 0; i < NUM_ALIENS; i++) {
        alienSpaceships[i].setPosicao(CalculaBezier3(alienSpaceships[i].pontosBezier,t));
    }
}
void AnimateAndUpdateCharacters(double dt) {
    Ponto Deslocamento; 
    Ponto Soma;
    // HERO 
    //Deslocamento.x = dt * heroSpaceship.getVelocidade().x * heroSpaceship.getDirecao().x;
    //Deslocamento.y = dt * heroSpaceship.getVelocidade().y * heroSpaceship.getDirecao().y;
    //Soma = Ponto(heroSpaceship.getPosicao().x + Deslocamento.x, heroSpaceship.getPosicao().y + Deslocamento.y);
    //heroSpaceship.setPosicao(Soma);
    // ALIENS

    AvancaComBezier();

    DrawAllTheCity();
}

void desenhaAlienBullets() {
    if (alienBullet[shotIndex].getMoving()) {
        alienBullet[shotIndex].desenha(true);
    }
}

void AnimateHeroShots (double dt) {
    Ponto Deslocamento; 
    Ponto Soma;
    // BULLET
    bullet.setMoving(true);
    Deslocamento.x = dt * bullet.getVelocidade().x * bullet.getDirecao().x;
    Deslocamento.y = dt * bullet.getVelocidade().y * bullet.getDirecao().y;
    Soma = Ponto(bullet.getPosicao().x + Deslocamento.x, bullet.getPosicao().y + Deslocamento.y);
    bullet.setPosicao(Soma);
}

void AnimateAlienShots (double dt, int index) {
    Ponto Deslocamento; 
    Ponto Soma;
    // BULLET
    Deslocamento.x = dt * alienBullet[index].getVelocidade().x * alienBullet[index].getDirecao().x;
    Deslocamento.y = dt * alienBullet[index].getVelocidade().y * alienBullet[index].getDirecao().y;
    Soma = Ponto(alienBullet[index].getPosicao().x + Deslocamento.x, alienBullet[index].getPosicao().y + Deslocamento.y);
    alienBullet[index].setPosicao(Soma);
}

void DrawAllTheCity() {
    int cntbuilding = 0, cnthouse = 0;
    int nextposdraw = 0;
    for (int i = 0; i < NUM_BUILDINGS; i++) {
        if (nextposdraw < 100) {
            building[i].setPosicao(Ponto(nextposdraw, 8.5));
            if (building[i].getMoving()) {
                building[i].desenha(true);
            }
            else {
                building[i].setPosicao(Ponto(10, 10));
                building[i].desenha(true);
            }
            nextposdraw += 12;  // Aumenta para o proximo setor de desenho
        }
        else {
            nextposdraw = 0;
        }
    }
    nextposdraw = 8;
    for (int i = 0; i < NUM_HOUSES; i++) {
        if (nextposdraw < 100) {
            house[i].setPosicao(Ponto(nextposdraw+3, 12));
            if (house[i].getMoving()) {
                house[i].desenha(true);
            }
            nextposdraw += 15;  // Aumenta para o proximo setor de desenho
        }
        else {
            nextposdraw = 0;
        }
    }
}
void DrawAllAlienSpaceShips () {
    for (int i = 0; i < NUM_ALIENS; i++) {   
        if (alienSpaceships[i].getMoving()) {
            alienSpaceships[i].desenha(true);
        }
    }
}

void DefinesBezierCurves(bool curveDireciton) {
    int cont = 0;
    float spacesize = alienSpaceships[0].getDrawning()->maxcol * 0.40;
    if (curveDireciton == true) {
        for (int i = 0;i < NUM_ALIENS; i++) { 
            if (cont < 5) {    
                alienSpaceships[i].pontosBezier[0] = Ponto(cont*12+spacesize, 70);
                alienSpaceships[i].pontosBezier[1] = Ponto((cont*12)+spacesize + 3, 80);
                alienSpaceships[i].pontosBezier[2] = Ponto((cont*12)+spacesize + 6, 60);
                cont++;
            }
            else {
                cont = 0;
            }
        }
    } else {

        for (int i = 0;i < NUM_ALIENS; i++) { 
            if (cont < 5) {              
                alienSpaceships[i].pontosBezier[0] = Ponto(alienSpaceships[i].pontosBezier[2].x, 60);
                alienSpaceships[i].pontosBezier[1] = Ponto(alienSpaceships[i].pontosBezier[1].x - 3, 80);
                alienSpaceships[i].pontosBezier[2] = Ponto(alienSpaceships[i].pontosBezier[0].x - 6, 70);
                cont++;
            }
            else {
                cont = 0;
            }
        }
    }
}

void InitializeCharacters() {
    int i, cont = 0;
    Min = Ponto (0, 0);
    Max = Ponto (100, 100);

    // Inicializa nave o heroi
    heroSpaceship = SpaceShip(HERO);
    heroSpaceship.setMatrixDrawning(matrixDrawHero);
    heroSpaceship.setPosicao(Ponto(20,20));         // Posicao inicial do heroi
    heroSpaceship.setEscala(Ponto(0.4, 0.4));
    heroSpaceship.setVelocidade(Ponto((Max.x - Min.x)/tempo, (Max.y - Min.y)/tempo));
    heroSpaceship.criaEnvelope();
    // Incializa os ojetos da cidade
    for (i = 0; i < NUM_BUILDINGS; i++) {
        building[i] = Instancia(BUILD);
        building[i].setMatrixDrawning(matrixDrawBuilding);
        building[i].setEscala(Ponto(1.5, 1.5));
        building[i].criaEnvelope();
        building[i].setMoving(true);
    }
    for (i = 0; i < NUM_HOUSES; i++) {
        house[i] = Instancia(HOUSE);
        house[i].setMatrixDrawning(matrixDrawHouse);
        house[i].setEscala(Ponto(0.8,0.8));
        house[i].criaEnvelope();
        house[i].setMoving(true);
    }
    // Incializa as naves alienigenas
    for (i = 0; i < NUM_ALIENS; i++) {
        alienSpaceships[i] = SpaceShip(ALIEN);
        if (i < 5) {
            alienSpaceships[i].setMoving(true);                     // Inicializa 5 naves
        } else {
            alienSpaceships[i].setMoving(false);                    
        }
        alienSpaceships[i].setRotacao(180);
        alienSpaceships[i].setMatrixDrawning(matrixDrawAlien);
        alienSpaceships[i].setEscala(Ponto(0.4, 0.4));
        alienSpaceships[i].setVelocidade(Ponto((Max.x - Min.x)/tempo,(Max.y - Min.y)/tempo));
        alienSpaceships[i].criaEnvelope();
    }
    DefinesBezierCurves(true);
    // Projeteis
    bullet = Instancia(BULLET);
    bullet.setMatrixDrawning(matrixDrawBullet);
    bullet.setVelocidade(Ponto((Max.x - Min.x)/1.3,(Max.y - Min.y)/1.3));
    for (i = 0; i < NUM_ALIENS; i++) {
        alienBullet[i] = Instancia(BULLET);
        alienBullet[i].setMatrixDrawning(matrixDrawBullet);
        alienBullet[i].setVelocidade(Ponto((Max.x - Min.x)/3.3,(Max.y - Min.y)/3.3));
    }
}
// **********************************************************************
// OpenGL Functions
// **********************************************************************
void init()
{
    initBackGroundTex();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    // Lendo os arquivos txt de cada obejto
    matrixDrawHero->readSketch("hero-spaceship.txt");
    matrixDrawAlien->readSketch("alien-spaceship.txt");
    matrixDrawBuilding->readSketch("building.txt");
    matrixDrawHouse->readSketch("house.txt"); 
    matrixDrawBullet->readSketch("bullet.txt");
    // inicializando os objetos
    
    InitializeCharacters();
    tempo = 3;
}
double nFrames = 0;
double AccumDeltaT = 0;
double TempoTotal = 0;
void animate()
{
    double dt;
    dt = Timer.getDeltaT();
    AccumDeltaT += dt;
    TempoTotal += dt;
    nFrames++;

    if (AccumDeltaT > 1.0 / 30)
    {
        AccumDeltaT = 0;
        glutPostRedisplay();
    }

    AnimateAndUpdateCharacters(dt);
    
    if (bullet.getMoving()) {
        AnimateHeroShots(dt);
    }
    
    if (bullet.getPosicao().x == Max.x || bullet.getPosicao().y == Max.y || bullet.getPosicao().x == Min.x || bullet.getPosicao().y == Min.y) {
        bullet.setMoving(false);
        bullet.setPosicao(Ponto(heroSpaceship.getPosicao().x+1/heroSpaceship.getEscala().x, heroSpaceship.getPosicao().y+1/heroSpaceship.getEscala().y));
    }

    if (TempoTotal > 3.0) {
        shotIndex = rand() % 5;
        alienBullet[shotIndex].setPosicao(alienSpaceships[shotIndex].getPosicao());
        alienBullet[shotIndex].setDirecao(Ponto(0, -1));
        alienBullet[shotIndex].setEscala(Ponto(0.2,0.2));
        alienBullet[shotIndex].setMoving(true);
        detectaColisoesNoMapa();
        TempoTotal = 0;
    }

    if (alienBullet[shotIndex].getPosicao().x == Max.x || alienBullet[shotIndex].getPosicao().y == Max.y || alienBullet[shotIndex].getPosicao().x == Min.x || alienBullet[shotIndex].getPosicao().y == Min.y) {
        alienBullet[shotIndex].setMoving(false);    
    }

    AnimateAlienShots(dt, shotIndex);
    detectaColisoes();


    TempoDaAnimacao += dt;
}

void reshape(int w, int h)
{
    AspectRatio = 1.0f * w / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);      // janela de exibicao
    
    glOrtho(0, WIDTH, 0, HEIGTH, 0, 1); // Janela de selecao

    PosicUser();
}

float var1, var2;
void keyboard(unsigned char key, int x, int y)
{
    float spacesize = heroSpaceship.getDrawning()->maxcol;
    switch (key)
    {
    case 27:
        exit(0); // a tecla ESC for pressionada
        break;
    case 32: // Tecla de tiro e start
        startgame = true;
        var1 = heroSpaceship.getPosicao().x + (heroSpaceship.getDrawning()->maxcol/2) * heroSpaceship.getEscala().x;
        var2 = heroSpaceship.getPosicao().y + (heroSpaceship.getDrawning()->maxrow/2) * heroSpaceship.getEscala().y;
        bullet.setPosicao(Ponto(var1,var2));
        bullet.setRotacao(heroSpaceship.getRotacao());
        bullet.setDirecao(Ponto(0, 1));
        bullet.setEscala(Ponto(0.2,0.2));
        bullet.setMoving(true);
        shotFlag = true;
        break;
    default:
        break;
    }
}

void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys )
	{
        case GLUT_KEY_UP: // movimenta para cima
            heroSpaceship.setPosicao(Ponto(heroSpaceship.getPosicao().x, heroSpaceship.getPosicao().y + 1));
            break;
        case GLUT_KEY_DOWN: // movimenta para baixo
            heroSpaceship.setPosicao(Ponto(heroSpaceship.getPosicao().x, heroSpaceship.getPosicao().y - 1));
            break;
        case GLUT_KEY_RIGHT: // movimenta a nave do heroi para esquerda
            heroSpaceship.setPosicao(Ponto(heroSpaceship.getPosicao().x+1, heroSpaceship.getPosicao().y));
            heroSpaceship.setDirecao(Ponto (1,0));
            break;
        case GLUT_KEY_LEFT: // movimenta a nave do heroi para esquerda
            heroSpaceship.setPosicao(Ponto(heroSpaceship.getPosicao().x-1, heroSpaceship.getPosicao().y));
            heroSpaceship.setDirecao(Ponto (-1,0));
            break;
        default:
            break;
    }
}
// Fuction to write in the screen
void drawString(float x, float y, float z, string str)
{
    glRasterPos3f(x, y, z);

    for (string::iterator it = str.begin(); it != str.end(); ++it)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *it); // Updates the position
    }
}
void drawRetBackGround() {
    glBegin ( GL_QUADS );
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glEnd();
}
void drawBackground() {
    PosicUser();
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    {
        glTranslatef ( 0.0f, 0.0f, -5.0f );
        glScalef(7,5,0);
        glBindTexture(GL_TEXTURE_2D, BackTex);
        drawRetBackGround();
    }
    glPopMatrix();
}
bool gaming = true;
bool ganhou = false;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawBackground();
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(0, WIDTH, 0, HEIGTH, 0, 1); // Janela de selecao
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //if (gaming) {
        DrawAllTheCity();
        if (bullet.getMoving()) {
            shotBullet();
        } 
        DrawAllAlienSpaceShips();
    
        heroSpaceship.desenha(true);
        glPushMatrix();
        {    
            glTranslated(heroSpaceship.getPosicao().x, heroSpaceship.getPosicao().y, 0);
            glScalef(heroSpaceship.getEscala().x, heroSpaceship.getEscala().y, 0);
            heroSpaceship.envelope.desenhaPoligono();
        } 
        glPopMatrix();
        desenhaAlienBullets();
        int cont = 0;
        for (int i = 0; i < NUM_ALIENS; i++) {
            if (alienSpaceships[i].getMoving()) {
                cont ++;
            }
        }
        if (cont == 0) {
            gaming = false;
        }
   // } else {
   //     glColor3f(0,0,0); 
   //     drawString(40, 70, 0, "ENG GAME");
   //     if (ganhou) {
   //         glColor3f(0,0,0); 
   //         drawString(40, 50, 0, "YOU WIN");
   //     } else {
   //         glColor3f(0,0,0); 
   //         drawString(40, 50, 0, "YOU LOOSE");
   //     }
   // }
    glutSwapBuffers();
}
// **********************************************************************
//  Main
// **********************************************************************
int main(int argc, char **argv)
{
    cout << "Programa OpenGL" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Game - SPACE WARSHIP");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc ( arrow_keys );
    // inicia o tratamento dos eventos
    glutMainLoop();

    return 0;
}