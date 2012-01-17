#include "Minimax.h"

MiniMax::MiniMax(int nivelIn)
{
    nivel=nivelIn;//0=principiante, 1=amateur, 2=experto
}

string MiniMax::tomarDesicion()
{
}

void MiniMax::definirVariables(char **estadoIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn)
{
    estado=estadoIn;
    posBlancasX=posBlancasXIn;
    posBlancasY=posBlancasYIn;
    posNegrasX=posNegrasXIn;
    posNegrasY=posNegrasYIn;
}

bool MiniMax::verificarJaque(bool color) //color=false => negras / color=true => blancas
{
    /*
        B = 66    b = 98
        C = 67    c = 99
        K = 75    k = 107
        P = 80    p = 112
        Q = 81    q = 113
     */

    int delta = color? 32 : 0;

    int reyX = color? posBlancasX[7] : posNegrasX[7];
    int reyY = color? posBlancasY[7] : posNegrasY[7];

    int dxDiago[] = {-1, 1,-1, 1};
    int dyDiago[] = {-1,-1, 1, 1};

    int dxRectas[] = { 0, 1, 0,-1};
    int dyRectas[] = {-1, 0, 1, 0};

    int dxCaballo[] = {-2,-2,-1,-1, 1, 1, 2, 2};
    int dyCaballo[] = {-1, 1,-2, 2,-2, 2,-1, 1};

    int dxRey[] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dyRey[] = {-1, 0, 1,-1, 1,-1, 0, 1};

    int idx=0;
    int count=1;
    int xx = 0;
    int yy = 0;
    bool respuesta = false;

    //alfiles-reinaDiagonal
    idx=0;
    count=1;
    while (true)
    {
        if(idx > 3) break;

        xx = reyX+(count*dxDiago[idx]);
        yy = reyY+(count*dyDiago[idx]);

        if(xx<0 || xx>5 || yy<0 || yy>5)
        {
            count=1;
            idx++;
        }
        else
        {
            if(estado[yy][xx] == ' ')
                count++;
            else{
                if(estado[yy][xx] == (81+delta) || estado[yy][xx] == (66+delta))
                    return true;
                else
                {
                    count=1;
                    idx++;
                }
            }
        }
    }

    //ReinaColumna
    idx=0;
    count=1;
    while (true)
    {
        if(idx > 3) break;

        xx = reyX+(count*dxRectas[idx]);
        yy = reyY+(count*dyRectas[idx]);

        if(xx<0 || xx>5 || yy<0 || yy>5)
        {
            count=1;
            idx++;
        }
        else
        {
            if(estado[yy][xx] == ' ')
                count++;
            else{
                if(estado[yy][xx] == (81+delta))
                    return true;
                else
                {
                    count=1;
                    idx++;
                }
            }
        }
    }

    //Caballos
    for (int i = 0; i < 8; ++i)
    {
        xx = reyX + dxCaballo[i];
        yy = reyY + dyCaballo[i];

        if(xx<0 || xx>5 || yy<0 || yy>5)
            continue;
        else
            if(estado[yy][xx] == (67+delta))
                return true;
    }

    //Peones
    if(color)
    {
        if(reyX>0 && reyY>0)
            if(estado[reyY-1][reyX-1] == 112)
                return true;

        if(reyX<5 && reyY>0)
            if(estado[reyY-1][reyX+1] == 112)
                return true;
    }
    else
    {
        if(reyX>0 && reyY<5)
            if(estado[reyY+1][reyX-1] == 80)
                return true;

        if(reyX<5 && reyY<5)
            if(estado[reyY+1][reyX+1] == 80)
                return true;
    }

    //Otro rey
    for (int i = 0; i < 8; ++i)
    {
        xx = reyX + dxRey[i];
        yy = reyY + dyRey[i];

        if(xx<0 || xx>5 || yy<0 || yy>5)
            continue;
        else
            if(estado[yy][xx] == (75+delta))
                return true;
    }

    return respuesta;
}

