#include "Mapa.h"

Mapa::Mapa()
{
}

int Mapa::pesoPeon(int x, int y)
{
    return Mapa::peon[x][y];
}

int Mapa::pesoCaballoAlfil(int x, int y)
{
    return caballoAlfil[x][y];
}

int Mapa::pesoReina(int x, int y)
{
    return reina[x][y];
}

int Mapa::pesoRey(int x, int y)
{
    return rey[x][y];
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
