#ifndef NODO_H
#define NODO_H

#include <string>
#include <iostream>

using namespace std;

class Nodo
{
private:
    int *posBlancasX;
    int *posBlancasY;
    int *posNegrasX;
    int *posNegrasY;
    char **estado;
    int nivel;
    int valor;
    string quienSoy;
    string decision;
    Nodo* padre;

public:
    Nodo(Nodo* padreIn, int nivelIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn, char **estadoIn, string quienSoyIn);
    ~Nodo();
    void actualizarDesicion(int valorIn, string cualHijo);

    char** getEstado();
    int* getPosBlancasX();
    int* getPosBlancasY();
    int* getPosNegrasX();
    int* getPosNegrasY();
    Nodo* getPadre();
    string getDecision();
    int getNivel();
    string getQuiensoy();
    int getValor();
};

#endif // NODO_H
