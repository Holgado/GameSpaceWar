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

Temporizador Timer;
MatrixDrawning *matrixDrawHero = new MatrixDrawning();
MatrixDrawning *matrixDrawAlien = new MatrixDrawning();
MatrixDrawning *matrixDrawBuilding = new MatrixDrawning();
MatrixDrawning *matrixDrawHouse = new MatrixDrawning();

Instancia building[NUM_BUILDINGS];
Instancia house[NUM_HOUSES];
SpaceShip alienSpaceships[NUM_ALIENS];

SpaceShip heroSpaceship = SpaceShip(HERO);
GLuint BackTex;

Ponto Max, Min;

int tempo = 5;
bool startgame = false;
float TempoDaAnimacao;
// functions

void initBackGroundTex (void) {
    BackTex = LoadTexture("background.jpg");
}

void AnimateAndUpdateCharacters(double dt) {
    Ponto Deslocamento; 
    Deslocamento.x = dt * heroSpaceship.getVelocidade().x * heroSpaceship.getDirecao().x;
    Deslocamento.y = dt * heroSpaceship.getVelocidade().y * heroSpaceship.getDirecao().y;
    Ponto Soma = Ponto(heroSpaceship.getPosicao().x + Deslocamento.x, heroSpaceship.getPosicao().y + Deslocamento.y);
    heroSpaceship.setPosicao(Soma);
}
void DrawAllTheCity() {
    int cntbuilding = 0, cnthouse = 0;
    int nextposdraw;
    house[0].setPosicao(Ponto(10,0));
    house[0].desenha();
    for (int i = 0; i < NUM_BUILDINGS+NUM_HOUSES; i++) {
        if (i % 2 == 0) {
            if (cntbuilding < NUM_BUILDINGS) {
                building[cntbuilding].setPosicao(Ponto(nextposdraw, 0));
                building[cntbuilding].desenha();
                nextposdraw = building[cntbuilding].getDrawning()->maxcol;
                cntbuilding++;
            }
        } else {
            if (cnthouse < NUM_HOUSES) {
                house[cnthouse].setPosicao(Ponto(nextposdraw, 0));
                house[cnthouse].desenha();
                nextposdraw = house[cnthouse].getDrawning()->maxcol;
                cnthouse++;
            }
        } 
    }
}
void InitializeCharacters() {
    int i;
    heroSpaceship.setMatrixDrawning(matrixDrawHero);
    heroSpaceship.setPosicao(Ponto(20,15));

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
        alienSpaceships[i].setMatrixDrawning(matrixDrawAlien);
    }
    
}

void init()
{
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
// **********************************************************************
//
// **********************************************************************

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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);      // janela de exibicao
    glOrtho(0, 100, 0, 100, 0, 1); // Janela de selecao
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
            heroSpaceship.setPosicao(Ponto(heroSpaceship.getPosicao().x + 1, heroSpaceship.getPosicao().y));
            heroSpaceship.setDirecao(Ponto(1, 0));
            break;
        case GLUT_KEY_LEFT: // movimenta a nave do heroi para esquerda
            heroSpaceship.setPosicao(Ponto(heroSpaceship.getPosicao().x - 1, heroSpaceship.getPosicao().y));
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
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(100.0f, 0.0f);
    glVertex2f( 1.0f, -1.0f);
    glTexCoord2f(100.0f, 100.0f);
    glVertex2f( 1.0f,  1.0f);
    glTexCoord2f(0.0f, 100.0f);
    glVertex2f(-1.0f,  1.0f);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (!startgame) {
        glPushMatrix();
        {
            glColor3f(0,0,0.2);
            heroSpaceship.desenha();
            DrawAllTheCity();
            glEnd();
            glColor3f(0,0,0);
            drawString(10, 40, 0.0, "Clique SPACE para inicar o Jogo");
        }
        glPopMatrix();
    } else {
        glPushMatrix();
        {
            //glClear(GL_COLOR_BUFFER_BIT);
            glTranslatef ( 0.0f, 0.0f, 1.0f );
            glBindTexture(GL_TEXTURE_2D, BackTex);
            drawRetBackGround();
    
        }
        glPopMatrix();
    }
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    cout << "Programa OpenGL" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
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