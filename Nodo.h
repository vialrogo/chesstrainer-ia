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
    Nodo* padre;

public:
    Nodo(Nodo* padreIn, int nivelIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn, char **estadoIn);
    void actualizarDesicion(int valorIn, string quiensoyIn);

    char** getEstado();
    int* getPosBlancasX();
    int* getPosBlancasY();
    int* getPosNegrasX();
    int* getPosNegrasY();
};

#endif // NODO_H
