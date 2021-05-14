class HeroSpaceShip {
    int life;
    float posx;
    float posy;
    static float posz = 10;
    float aimingAngle;
}


class RGB {
    public:
    int r,g,b;
    void imprime()
    {
        cout << "Cor: " << setw(4) << g << setw(4) << r << setw(4) << b;
    }
};

RGB PaletteGlobal[100];

class ModeloMatricial{
    int M[50][50];
    void leModelo(const char *nome);
    void desenhaModelo();
};