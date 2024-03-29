#include "Mapa.h"

//Definicion de variables estaticas

int Mapa::peonBlanco[6][6]={{2,2,2,2,2,2},
                            {4,5,5,5,5,4},
                            {4,5,5,5,5,4},
                            {4,5,5,5,5,4},
                            {4,5,5,5,5,4},
                            {4,5,5,5,5,4}};

int Mapa::peonNegro[6][6]={{4,5,5,5,5,4},
                           {4,5,5,5,5,4},
                           {4,5,5,5,5,4},
                           {4,5,5,5,5,4},
                           {4,5,5,5,5,4},
                           {2,2,2,2,2,2}};

int Mapa::caballoAlfil[6][6]={{13,14,14,14,14,13},
                              {14,15,15,15,15,14},
                              {14,15,16,16,15,14},
                              {14,15,16,16,15,14},
                              {14,15,15,15,15,14},
                              {13,14,14,14,14,13}};

int Mapa::reina[6][6]={{44,44,44,44,44,44},
                       {44,45,45,45,45,44},
                       {44,45,46,46,45,44},
                       {44,45,46,46,45,44},
                       {44,45,45,45,45,44},
                       {44,44,44,44,44,44}};

int Mapa::rey[6][6]={{1002,1000,1000,1000,1000,1002},
                     {1000,998,998,998,998,1000},
                     {1000,998,998,998,998,1000},
                     {1000,998,998,998,998,1000},
                     {1000,998,998,998,998,1000},
                     {1002,1000,1000,1000,1000,1002}};

int Mapa::dxDiago[4] = {-1, 1,-1, 1};
int Mapa::dyDiago[4] = {-1,-1, 1, 1};

int Mapa::dxRectas[4] = { 0, 1, 0,-1};
int Mapa::dyRectas[4] = {-1, 0, 1, 0};

int Mapa::dxCaballo[8] = {-2,-2,-1,-1, 1, 1, 2, 2};
int Mapa::dyCaballo[8] = {-1, 1,-2, 2,-2, 2,-1, 1};

int Mapa::dxRey[8] = {-1,-1,-1, 0, 0, 1, 1, 1};
int Mapa::dyRey[8] = {-1, 0, 1,-1, 1,-1, 0, 1};

char Mapa::blancas[8] = {'A','B','C','D','E','F','G','H'};
char Mapa::negras[8] = {'a','b','c','d','e','f','g','h'};

//int Mapa::dxRectaArriba=0;
//int Mapa::dyRectaArriba=-1;
//int Mapa::dxRectaAbajo=0;
//int Mapa::dyRectaAbajo=1;

//Definicion de metodos

Mapa::Mapa()
{
}

int Mapa::pesoPeonBlanco(int x, int y)
{
    if(x==-1 && y==-1) return 0;
    return Mapa::peonBlanco[x][y];
}

int Mapa::pesoPeonNegro(int x, int y)
{
    if(x==-1 && y==-1) return 0;
    return Mapa::peonNegro[x][y];
}

int Mapa::pesoCaballoAlfil(int x, int y)
{
    if(x==-1 && y==-1) return 0;
    return caballoAlfil[x][y];
}

int Mapa::pesoReina(int x, int y)
{
    if(x==-1 && y==-1) return 0;
    return reina[x][y];
}

int Mapa::pesoRey(int x, int y)
{
    if(x==-1 && y==-1) return 0;
    return rey[x][y];
}

int Mapa::getDxDiago(int i)
{
    return dxDiago[i];
}

int Mapa::getDyDiago(int i)
{
    return dyDiago[i];
}

int Mapa::getDxRectas(int i)
{
    return dxRectas[i];
}

int Mapa::getDyRectas(int i)
{
    return dyRectas[i];
}

int Mapa::getDxCaballo(int i)
{
    return dxCaballo[i];
}

int Mapa::getDyCaballo(int i)
{
    return dyCaballo[i];
}

int Mapa::getDxRey(int i)
{
    return dxRey[i];
}

int Mapa::getDyRey(int i)
{
    return dyRey[i];
}

char Mapa::getBlanca(int i)
{
    return blancas[i];
}

char Mapa::getNegra(int i)
{
    return negras[i];
}

//int main()
//{
//    Mapa obj;
//    obj.peon[3][4]=3;
//    for (int var = 0; var < total; var++) {
//        cout<<"peon: ";
//        for (int var2 = 0; var2 < 6; var2++) {
//            cout<<obj.pesoPeon(var,var2)<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<endl;
//    for (int var = 0; var < total; var++) {
//        cout<<"caballo y alfil: ";
//        for (int var2 = 0; var2 < 6; var2++) {
//            cout<<obj.pesoCaballoAlfil(var,var2)<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<endl;
//    for (int var = 0; var < total; var++) {
//        cout<<"Reina: ";
//        for (int var2 = 0; var2 < 6; var2++) {
//            cout<<obj.pesoReina(var,var2)<<" ";
//        }
//        cout<<endl;
//    }
//    cout<<endl;
//    for (int var = 0; var < total; var++) {
//        cout<<"Rey: ";
//        for (int var2 = 0; var2 < 6; var2++) {
//            cout<<obj.pesoRey(var,var2)<<" ";
//        }
//        cout<<endl;
//    }
//}
