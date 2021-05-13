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

// includes 


// functions
void animate();
void keyboard(unsigned char key, int x, int y);


int  main ( int argc, char** argv )
{
    cout << "Programa OpenGL" << endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );
    glutInitWindowPosition(0,0);
    glutInitWindowSize(1000, 500);
    glutCreateWindow("Game - SPACE WARSHIP");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutReshapeFunc (reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_keys);

    // inicia o tratamento dos eventos
    glutMainLoop ( );

    return 0;
}
void animate()
{
    double dt;
    dt = T.getDeltaT();
    AccumDeltaT += dt;
    TempoTotal += dt;
    nFrames++;

    if (AccumDeltaT > 1.0/30) // fixa a atualiza��o da tela em 30
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
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Define a area a ser ocupada pela area OpenGL dentro da Janela
    glViewport(0, 0, w, h);
    // Define os limites logicos da area OpenGL dentro da Janela
    glOrtho(Min.x,Max.x,
            Min.y,Max.y,
            0,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void display( void )
{

	// Limpa a tela coma cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

    // Define os limites dentro da Janela
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	// Coloque aqui as chamadas das rotinas que desenham os objetos
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

	glLineWidth(1);
	glColor3f(1,1,1); // R, G, B  [0..1]
    // desenha cidade

	glutSwapBuffers();
}
void keyboard ( unsigned char key, int x, int y )
{
    PoligonoCSG poligonoCsg;
    FileService fileService;
	switch (key)
	{
		case 27:            
			exit (0);   // a tecla ESC for pressionada
			break;
        case GLUT_KEY_UP: // movimenta a mira da nave do heroi no sentido horario
            
            break;
        case GLUT_KEY_DOWN: // movimenta a mira da nave do heroi no sentido antihorario

            break;
        case GLUT_KEY_LEFT: // movimenta a nave do heroi para esquerda

            break;
        case GLUT_KEY_RIGHT: // movimenta a nave do heroi para esquerda

            break;
		default:
			break;
	}
}