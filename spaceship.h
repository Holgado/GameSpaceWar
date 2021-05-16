#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class RGB {
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
    RGB mat[10];
    MatrixDrawning() { }
    void readSketch(string filename) {
        ifstream input;
        string line;
        int totCores, lineNumber = 0;
        int row, col;
        input.open(filename, ios::in);
        if (!input) {
            cout << "Erro ao abrir " << filename << ". " << endl;
            exit(0);
        }
        while (!input.eof()) {
            getline(input, line);
            if (line == "#CORES") {
                input >> totCores;
                for (int i = 0; i < totCores; i++) {
                    input >> mat[i].r >> mat[i].g >> mat[i].b;
                }
            }
            if (line == "#OBJETO") {
                input >> row >> col;
                for (int i = 0; i < row; i++) {
                    getline(input, line);
                    vector<string> auxstr = split(line, ' ');
                    for (int j = 0; j < auxstr.size(); j++) {
                        cout << auxstr.at(j);
                    }                                            
                }
            }
            lineNumber ++;
        }
    }
    void drawModel() {
        // le a matrix de cores e de numeros e desenhas pixels na posicao
        
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
};
class SpaceShip {
private:
    MatrixDrawning drawning;
protected:
    int life;
    float posx;
    float posy;
    float posz = 10;
public:
    SpaceShip() {}

    void setLife(int value) {
        life = value;
    }
    void setPosx(float _posx) {
        posx = _posx;
    }
    void setPosy(float _posx) {
        posx = _posx;
    }
    int getLife() {
        return life;
    }
    float getPosx() {
        return posx;
    }
    float getPosy() {
        return posy;
    }
    void setMatrixDrawning(string filename) {
        drawning.readSketch(filename);
    }
    MatrixDrawning getDrawning() {
        return drawning;
    }
};

class HeroSpaceShip : SpaceShip {
private:
    float aimingAngle;
    MatrixDrawning drawning;
public:
    void setAimingAngle(float angle) {
        // limita o valor do angulo da mira no intervalo de -80 a 80
        if (angle > 80) {
            angle = 80;
        } 
        if (angle < -80) {
            angle = -80;
        }
        aimingAngle = angle;
    }
    float getAimingAngle() {
        return aimingAngle;
    }
    void setMatrixDrawning(string filename) {
        drawning.readSketch(filename);
    }
    MatrixDrawning getDrawning() {
        return drawning;
    }
};