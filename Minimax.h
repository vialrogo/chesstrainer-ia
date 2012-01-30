#ifndef MINIMAX_H
#define MINIMAX_H

#include <string>
#include "Mapa.h"
#include "Nodo.h"
#include <QStack>
#include <QList>
#include <iostream>
#include <sstream>

using namespace std;

class MiniMax
{
private:
    int nivel;
    char **estado;
    int *posBlancasX;
    int *posBlancasY;
    int *posNegrasX;
    int *posNegrasY;

    Mapa mapa;
    int calcularHeuristica(Nodo *elNodo);
    QList<Nodo*> expandir (Nodo *elNodo);
    void imprimir(Nodo *elNodo);
    void imprimir(char **estadoIn);

public:
    MiniMax(int nivelIn);
    string tomarDesicion();
    void definirVariables(char **estadoIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn, bool copia);
    bool verificarJaque(bool color);
    int sePuedeMover(int xDestino, int yDestino, int ficha, bool color);
};

#endif // MINIMAX_H
