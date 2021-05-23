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
#define NUM_ALIENS 50
#define NUM_BUILDINGS 4
#define NUM_HOUSES 3
#define WIDTH 100
#define HEIGTH 100

Temporizador Timer;
MatrixDrawning *matrixDrawHero = new MatrixDrawning();
MatrixDrawning *matrixDrawAlien = new MatrixDrawning();
MatrixDrawning *matrixDrawBuilding = new MatrixDrawning();
MatrixDrawning *matrixDrawHouse = new MatrixDrawning();

Instancia building[NUM_BUILDINGS];
Instancia house[NUM_HOUSES];
SpaceShip alienSpaceships[NUM_ALIENS];
SpaceShip heroSpaceship;

GLuint BackTex;

Ponto Max, Min;

int tempo = 5;
bool startgame = false;
float TempoDaAnimacao;
GLfloat AspectRatio, AngY=0;
// **********************************************************************
//  Functions
// **********************************************************************
void DrawAllTheCity();
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

void AnimateAndUpdateCharacters(double dt) {
    Ponto Deslocamento; 
    Ponto Soma;
    // HERO 
    Deslocamento.x = dt * heroSpaceship.getVelocidade().x * heroSpaceship.getDirecao().x;
    
    Deslocamento.y = dt * heroSpaceship.getVelocidade().y * heroSpaceship.getDirecao().y;
    
    Soma = Ponto(heroSpaceship.getPosicao().x + Deslocamento.x, heroSpaceship.getPosicao().y + Deslocamento.y);
    
    heroSpaceship.setPosicao(Soma);
    // ALIENS
    double t;
    t = TempoDaAnimacao/tempo;
    Ponto pontosBezier[3];
    
    for (int i = 0;i < NUM_ALIENS; i++) {
        if (alienSpaceships[i].getMoving()) { 
            pontosBezier[0] = Ponto(alienSpaceships->getPosicao().x, alienSpaceships->getPosicao().y);
            pontosBezier[1] = Ponto(alienSpaceships->getPosicao().x+3, alienSpaceships->getPosicao().y+3);
            pontosBezier[2] = Ponto(alienSpaceships->getPosicao().x+6, alienSpaceships->getPosicao().y-3);
            alienSpaceships[i].setPosicao(CalculaBezier3(pontosBezier,t));
        }
    }
    DrawAllTheCity();
}
void DrawAllTheCity() {
    int cntbuilding = 0, cnthouse = 0;
    int nextposdraw = 0;
    for (int i = 0; i < NUM_BUILDINGS; i++) {
        if (nextposdraw < 100) {
            building[i].setPosicao(Ponto(nextposdraw, 8.5));
            building[i].desenha();
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
            house[i].desenha();
            nextposdraw += 15;  // Aumenta para o proximo setor de desenho
        }
        else {
            nextposdraw = 0;
        }
    }
}
void DrawAllAlienSpaceShips () {
    int cont = 10;
    for (int i = 0; i < NUM_ALIENS; i++) {   
        if (alienSpaceships[i].getMoving()) {
            if (cont < 100) {
                alienSpaceships[i].setPosicao(Ponto(cont,40));         // Set o setor incial
                alienSpaceships[i].desenha();
                cont+=10;
            }
            else {
                cont = 0;
            }
        }
    }
}

void InitializeCharacters() {
    int i, cont = 0; tempo = 25;
    Min = Ponto (0, 0);
    Max = Ponto (100, 100);

    // Inicializa nave o heroi
    heroSpaceship = SpaceShip(HERO);
    heroSpaceship.setMatrixDrawning(matrixDrawHero);
    heroSpaceship.setPosicao(Ponto(20,30));         // Posicao inicial do heroi

    // Incializa os ojetos da cidade
    for (i = 0; i < NUM_BUILDINGS; i++) {
        building[i] = Instancia(BUILD);
        building[i].setMatrixDrawning(matrixDrawBuilding);
    }
    for (i = 0; i < NUM_HOUSES; i++) {
        house[i] = Instancia(HOUSE);
        house[i].setMatrixDrawning(matrixDrawHouse);
    }
    // Incializa as naves alienigenas
    for (i = 0; i < NUM_ALIENS; i++) {
        alienSpaceships[i] = SpaceShip(ALIEN);
        if (i < 5) {
            alienSpaceships[i].setMoving(true);                     // Inicializa 5 naves
        }
        alienSpaceships[i].setRotacao(180);
        alienSpaceships[i].setMatrixDrawning(matrixDrawAlien);
        alienSpaceships[i].setVelocidade(Ponto((Max.x - Min.x)/tempo,(Max.y - Min.y)/tempo));
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
    // inicializando os objetos
    
    InitializeCharacters();
    tempo = 25;
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
    if (TempoTotal > 5.0)
    {
        //cout << "Tempo Acumulado: "  << TempoTotal << " segundos. ";
        //cout << "Nros de Frames sem desenho: " << nFrames << endl;
        //cout << "FPS(sem desenho): " << nFrames/TempoTotal << endl;
        TempoTotal = 0;
        nFrames = 0;
    }
    AnimateAndUpdateCharacters(dt);
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


void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0); // a tecla ESC for pressionada
        break;
    case 32: // Tecla SPACE de tiro e start
        startgame = true;
        break;
    default:
        break;
    }
}

void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys )
	{
        case GLUT_KEY_UP: // movimenta a mira da nave do heroi no sentido horario
            heroSpaceship.setAimingAngle(heroSpaceship.getAimingAngle() + 1);
            break;
        case GLUT_KEY_DOWN: // movimenta a mira da nave do heroi no sentido antihorario
            heroSpaceship.setAimingAngle(heroSpaceship.getAimingAngle() - 1);
            break;
        case GLUT_KEY_RIGHT: // movimenta a nave do heroi para esquerda
            heroSpaceship.setRotacao(-10);
            heroSpaceship.setPosicao(Ponto(heroSpaceship.getPosicao().x + 5, heroSpaceship.getPosicao().y));
            heroSpaceship.setDirecao(Ponto(1, 0));
            break;
        case GLUT_KEY_LEFT: // movimenta a nave do heroi para esquerda
            heroSpaceship.setRotacao(10);
            heroSpaceship.setPosicao(Ponto(heroSpaceship.getPosicao().x - 5, heroSpaceship.getPosicao().y));
            heroSpaceship.setDirecao(Ponto(-1, 0));
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
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *it); // Updates the position
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
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);


    drawBackground();

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glOrtho(0, WIDTH, 0, HEIGTH, 0, 1); // Janela de selecao
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    heroSpaceship.desenha();
    DrawAllTheCity();
    DrawAllAlienSpaceShips();
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