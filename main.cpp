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

// Definitions
Temporizador Timer;
// functions
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.2f);   
}


double nFrames=0;
double AccumDeltaT=0;
double TempoTotal=0;
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

    if (AccumDeltaT > 1.0/30) 
    {
        AccumDeltaT = 0;
        glutPostRedisplay();
    }
    if (TempoTotal > 5.0)
    {
        cout << "Tempo Acumulado: "  << TempoTotal << " segundos. " ;
        cout << "Nros de Frames sem desenho: " << nFrames << endl;
        cout << "FPS(sem desenho): " << nFrames/TempoTotal << endl;
        TempoTotal = 0;
        nFrames = 0;
    }
}

void reshape( int w, int h )
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);  // janela de exibicao 
    glOrtho(0, 50, 0, 50, 0,1); // Janela de selecao
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
bool startgame = false;
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:            
			exit (0);           // a tecla ESC for pressionada
			break;
        case GLUT_KEY_UP:       // movimenta a mira da nave do heroi no sentido horario
            
            break;
        case GLUT_KEY_DOWN:     // movimenta a mira da nave do heroi no sentido antihorario

            break;
        case GLUT_KEY_LEFT:     // movimenta a nave do heroi para esquerda

            break;
        case GLUT_KEY_RIGHT:    // movimenta a nave do heroi para esquerda

            break;
        case 32:                // Tecla SPACE de tiro e start
            startgame = true;

            break;
		default:
			break;
	}
}
void drawString(float x, float y, float z, string str) {
  glRasterPos3f(x, y, z);

   for (string::iterator it=str.begin(); it!=str.end(); ++it) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *it);  // Updates the position
  }
}

void display( void )
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  
    
    if (!startgame) {
        glPushMatrix(); 
        {
            glColor3f(0,0,0);
            drawString(10, 10, 0.0, "Clique ENTER para inicar o Jogo");
        }    
        glPopMatrix();
    } else {
        glPushMatrix();
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }
        glPopMatrix();
    }
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
    cout << "Programa OpenGL" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Game - SPACE WARSHIP");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutReshapeFunc (reshape);
    glutKeyboardFunc(keyboard);

    // inicia o tratamento dos eventos
    glutMainLoop();

    return 0;
}