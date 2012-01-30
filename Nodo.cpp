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
    valor=(nivel%2==0)? -100000 : 100000;
}

Nodo::~Nodo()
{
    for(int i = 0; i < 6; i++)
    {
        delete[] estado[i];
        estado[i]=0;
    }
    delete[] estado;
    estado=0;

//    delete[] posBlancasX;
//    delete[] posBlancasY;
//    delete[] posNegrasX;
//    delete[] posNegrasY;
//    posBlancasX=0;
//    posBlancasY=0;
//    posNegrasX=0;
//    posNegrasY=0;

//    padre=0;
}

//para quien soy: Mayúscula=blancas Minúscula=negras; B=alfil, H=Caballo, K=rey, P=peón, Q=reina
void Nodo::actualizarDesicion(int valorIn, string cualHijo)
{
    if(nivel%2==0)
    {
       if(valor<=valorIn)
       {
           valor=valorIn;
           decision=cualHijo;
       }
    }
    else
    {
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

string Nodo::getQuiensoy()
{
    return quienSoy;
}

Nodo* Nodo::getPadre()
{
    return padre;
}

int Nodo::getValor()
{
    return valor;
}
