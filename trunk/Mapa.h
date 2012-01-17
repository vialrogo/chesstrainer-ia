#ifndef MAPA_H
#define MAPA_H

class Mapa
{
private:
    static int peon[6][6];
    static int caballoAlfil[6][6];
    static int reina[6][6];
    static int rey[6][6];

    //Desplazamiento de las fichas
//    static int dxRectaArriba;
//    static int dyRectaArriba;
//    static int dxRectaAbajo;
//    static int dyRectaAbajo;

public:
    Mapa();
    static int pesoPeon(int x, int y);
    static int pesoCaballoAlfil(int x, int y);
    static int pesoReina(int x, int y);
    static int pesoRey(int x, int y);

};

#endif // MAPA_H
