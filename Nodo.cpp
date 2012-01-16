#include "Nodo.h"

Nodo::Nodo(Nodo* padreIn, int nivelIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn, char **estadoIn)
{
    padre=padreIn;
    nivel=nivelIn;
    posBlancasX=posBlancasXIn;
    posBlancasY=posBlancasYIn;
    posNegrasX=posNegrasXIn;
    posNegrasY=posNegrasYIn;
    estado=estadoIn;

//    for (int var = 0; var < 8; var++) {
//        posBlancasXIn[var]=posBlancasX[var];
//        posBlancasYIn[var]=posBlancasY[var];
//        posNegrasXIn[var]=posNegrasX[var];
//        posNegrasYIn[var]=posNegrasYIn[var];
//    }

//    for (int var = 0; var < 6; var++) {
//        for (int var2 = 0; var2 < 6; var2++) {
//            estadoIn[var][var2]=estado[var][var2];
//        }
//    }

    quienSoy="";
    valor=0;
}

void Nodo::actualizarDesicion(int valorIn, string quiensoyIn)
{
    if(nivel%2==0){
        if(valor<=valorIn)
        {
            valor=valorIn;
            quienSoy=quiensoyIn;
        }
    }
    else{
        if(valor>=valorIn)
        {
            valor=valorIn;
            quienSoy=quiensoyIn;
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

