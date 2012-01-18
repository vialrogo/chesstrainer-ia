#include "Nodo.h"

Nodo::Nodo(Nodo* padreIn, int nivelIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn, char **estadoIn, string quienSoyIn)
{
    padre=padreIn;
    nivel=nivelIn;
    posBlancasX=posBlancasXIn;
    posBlancasY=posBlancasYIn;
    posNegrasX=posNegrasXIn;
    posNegrasY=posNegrasYIn;
    estado=estadoIn;

    quienSoy=quienSoyIn;
    decision="";
    valor=0;
}

//para quien soy: Mayúscula=blancas Minúscula=negras; B=alfil, H=Caballo, K=rey, P=peón, Q=reina
void Nodo::actualizarDesicion(int valorIn, string cualHijo)
{
    if(nivel%2==0){
        if(valor<=valorIn)
        {
            valor=valorIn;
            decision=cualHijo;
        }
    }
    else{
        if(valor>=valorIn)
        {
            valor=valorIn;
            decision=cualHijo;
        }
    }
}

char** Nodo::getEstado()
{
    return estado;
}

int* Nodo::getPosBlancasX()
{
    return posBlancasX;
}

int* Nodo::getPosBlancasY()
{
    return posBlancasY;
}

int* Nodo::getPosNegrasX()
{
    return posNegrasX;
}

int* Nodo::getPosNegrasY()
{
    return posNegrasY;
}

string Nodo::getDecision()
{
    return decision;
}

int Nodo::getNivel()
{
    return nivel;
}
