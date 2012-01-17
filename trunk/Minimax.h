#ifndef MINIMAX_H
#define MINIMAX_H

#include <string>
#include "Mapa.h"

using namespace std;

class MiniMax
{
private:
    char **estado;
    int *posBlancasX;
    int *posBlancasY;
    int *posNegrasX;
    int *posNegrasY;
    int nivel;

    Mapa mapa;

    char sePuedeMover(int x, int y);

public:
    MiniMax(int nivelIn);
    string tomarDesicion();
    void definirVariables(char **estadoIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn);
    bool verificarJaque(bool color);

};

#endif // MINIMAX_H
