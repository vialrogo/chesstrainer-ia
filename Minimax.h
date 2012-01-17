#ifndef MINIMAX_H
#define MINIMAX_H

#include <string>
#include "Mapa.h"

using namespace std;

class MiniMax
{
private:
    char **estadoInicial;
    int *posBlancasX;
    int *posBlancasY;
    int *posNegrasX;
    int *posNegrasY;
    int nivel;

    Mapa mapa;

    char sePuedeMover(int x, int y);

public:
    MiniMax(int nivelIn);
    string tomarDesicion(char **estadoInicialIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn);

};

#endif // MINIMAX_H
