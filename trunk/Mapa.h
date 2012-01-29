#ifndef MAPA_H
#define MAPA_H

class Mapa
{
private:
    static int peonBlanco[6][6];
    static int peonNegro[6][6];
    static int caballoAlfil[6][6];
    static int reina[6][6];
    static int rey[6][6];

    static int dxDiago[4];
    static int dyDiago[4];
    static int dxRectas[4];
    static int dyRectas[4];
    static int dxCaballo[8];
    static int dyCaballo[8];
    static int dxRey[8];
    static int dyRey[8];

    static char blancas[8];
    static char negras[8];

    //Desplazamiento de las fichas
//    static int dxRectaArriba;
//    static int dyRectaArriba;
//    static int dxRectaAbajo;
//    static int dyRectaAbajo;

public:
    Mapa();
    static int pesoPeonBlanco(int x, int y);
    static int pesoPeonNegro(int x, int y);
    static int pesoCaballoAlfil(int x, int y);
    static int pesoReina(int x, int y);
    static int pesoRey(int x, int y);

    static int getDxDiago(int i);
    static int getDyDiago(int i);
    static int getDxRectas(int i);
    static int getDyRectas(int i);
    static int getDxCaballo(int i);
    static int getDyCaballo(int i);
    static int getDxRey(int i);
    static int getDyRey(int i);

    static char getBlanca(int i);
    static char getNegra(int i);

};

#endif // MAPA_H
