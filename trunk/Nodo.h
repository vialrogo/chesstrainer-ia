#ifndef NODO_H
#define NODO_H

#include <string>

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
    double valor;
    string quienSoy;
    string decision;
    Nodo* padre;

public:
    Nodo(Nodo* padreIn, int nivelIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn, char **estadoIn, string quienSoyIn);
    void actualizarDesicion(int valorIn, string cualHijo);

    char** getEstado();
    int* getPosBlancasX();
    int* getPosBlancasY();
    int* getPosNegrasX();
    int* getPosNegrasY();
    string getDecision();
    int getNivel();
};

#endif // NODO_H
