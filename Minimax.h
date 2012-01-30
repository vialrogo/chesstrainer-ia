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

    Mapa mapa;
    int calcularHeuristica(Nodo *elNodo);
    QList<Nodo*> expandir (Nodo *elNodo);
    int *copiarBlancasX(int *blancasIn);
    int *copiarBlancasY(int *blancasIn);
    int *copiarNegrasX(int *negrasIn);
    int *copiarNegrasY(int *negrasIn);
    char **copiarEstado(char **estadoIn);
    int sePuedeMover(char **estado,int xOrigen, int yOrigen, int xDestino, int yDestino, int ficha, bool color);

    void imprimir(Nodo *elNodo);
    void imprimir(char **estadoIn);

public:
    MiniMax(int nivelIn);
    ~MiniMax();
    string tomarDesicion(int *posBlancasX,int *posBlancasY,int *posNegrasX,int *posNegrasY,char **estado);
//    void definirVariables(char **estadoIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn, bool copia);
    bool verificarJaque(bool color, int xRey, int yRey, char **estado);
    bool mateHumano(int *posBlancasX,int *posBlancasY,int *posNegrasX,int *posNegrasY,char **estado);
};

#endif // MINIMAX_H
