#include "Minimax.h"

MiniMax::MiniMax(int nivelIn)
{
    nivel=nivelIn;//0=principiante, 1=amateur, 2=experto
}

string MiniMax::tomarDesicion(char **estadoInicialIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn)
{
    estadoInicial=estadoInicialIn;
    posBlancasX=posBlancasXIn;
    posBlancasY=posBlancasYIn;
    posNegrasX=posNegrasXIn;
    posNegrasY=posNegrasYIn;


}

