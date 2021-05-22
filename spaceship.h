#ifndef SpaceShip_hpp
#define SpaceShip_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "Instancia.h"
using namespace std;

class SpaceShip : public Instancia {
private:
    int life;
    float aimingAngle;
    bool animando; 
public: 
    SpaceShip(){}

    SpaceShip(Modelos a) : Instancia() {
        tipo = a;
    }

    void setLife(int value) {
        life = value;
    }
    int getLife() {
        return life;
    }
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

};
#endif