#ifndef MatrixDrawning_hpp
#define MatrixDrawning_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

#include "Ponto.h"

#ifdef __linux__
#include <GL/glut.h>
#endif

class ColorsRGB {
public:
    int r,g,b;
    void imprime()
    {
        cout << "Cor: " << setw(4) << g << setw(4) << r << setw(4) << b;
    }
};

class MatrixDrawning {
public:    
    int M[50][50];
    ColorsRGB mat[10];
    int maxcol, maxrow;
    int maxcolor;
    MatrixDrawning() { }
    void readSketch(string filename) {
        ifstream input;
        string line;
        int totCores, lineNumber = 0;
        int row, col;
        int indexcolor;
        input.open(filename, ios::in);
        if (!input) {
            cout << "Erro ao abrir " << filename << ". " << endl;
            exit(0);
        }
        while (!input.eof()) {
            getline(input, line);
            if (line == "#CORES") {
                input >> totCores;
                maxcolor = totCores;
                for (int i = 1; i <= totCores; i++) {
                    input >> indexcolor >> mat[i].r >> mat[i].g >> mat[i].b;
                }
            }
            if (line == "#OBJETO") {
                input >> row >> col;
                maxcol = col;
                maxrow = row;
                for (int i = 0; i < row; i++) {
                    for (int j = 0; j < col; j++) {
                        input >> M[i][j];
                    }                                            
                }
            }
            lineNumber ++;
        }
    }
    void drawModel(Ponto pos) {
        // le a matrix de cores e de numeros e desenhas pixels na posicao
        int colorvalue;
        for (int i = 0; i < maxrow; i++) {
            for (int j = 0; j < maxcol; j++) {
                colorvalue = M[i][j];
                glColor3f(mat[colorvalue].r, mat[colorvalue].g, mat[colorvalue].b);
                drawPixelRet(i, j, pos.x, pos.y);
                
            }
            
        }
    }
    
private:
    vector<string> split(const string& s, char delimiter)
    {
        vector<string> tokens;
        string token;
        istringstream tokenStream(s);
        while (getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
    void drawPixelRet(int row, int col, int x, int y) {
        x = x + row;
        y = y + col;
        glPushMatrix();
        glTranslatef(x, y, 0);
        glBegin(GL_POLYGON); 
        {   
            glVertex3f (0, 0, 0.0);
            glVertex3f (1, 0, 0.0);
            glVertex3f (1, 1, 0.0);
            glVertex3f (0, 1, 0.0);
        }
        glEnd(); 
        glPopMatrix();
    }
};
#endif