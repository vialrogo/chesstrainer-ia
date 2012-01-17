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

int Mapa::peon[6][6]={{2,2,2,2,2,2},
                      {4,5,5,5,5,4},
                      {4,5,5,5,5,4},
                      {4,5,5,5,5,4},
                      {4,5,5,5,5,4},
                      {4,5,5,5,5,4}};

int Mapa::caballoAlfil[6][6]={{13,14,14,14,14,13},
                              {14,15,15,15,15,14},
                              {14,15,16,16,15,14},
                              {14,15,16,16,15,14},
                              {14,15,15,15,15,14},
                              {13,14,14,14,14,13}};

int Mapa::reina[6][6]={{44,44,44,44,44,44},
                       {44,45,45,45,45,44},
                       {44,45,46,46,45,44},
                       {44,45,46,46,45,44},
                       {44,45,45,45,45,44},
                       {44,44,44,44,44,44}};

int Mapa::rey[6][6]={{1002,1000,1000,1000,1000,1002},
                     {1000,998,998,998,998,1000},
                     {1000,998,998,998,998,1000},
                     {1000,998,998,998,998,1000},
                     {1000,998,998,998,998,1000},
                     {1002,1000,1000,1000,1000,1002}};

//int Mapa::dxRectaArriba=0;
//int Mapa::dyRectaArriba=-1;
//int Mapa::dxRectaAbajo=0;
//int Mapa::dyRectaAbajo=1;

#endif // MAPA_H
