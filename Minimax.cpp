#include "Minimax.h"

MiniMax::MiniMax(int nivelIn)
{
    nivel=nivelIn;//0=principiante, 1=amateur, 2=experto
}

//Calcula el valor para un nodo
int MiniMax::calcularHeuristica(Nodo *elNodo)
{
    int resultado=0;
    int *xBlancas=elNodo->getPosBlancasX();
    int *yBlancas=elNodo->getPosBlancasY();
    int *xNegras=elNodo->getPosNegrasX();
    int *yNegras=elNodo->getPosNegrasY();

    for (int var = 0; var < 4; var++) {
        resultado+=mapa.pesoPeon(xBlancas[var],yBlancas[var]);
    }
    resultado+=mapa.pesoCaballoAlfil(xBlancas[4],yBlancas[4]);
    resultado+=mapa.pesoCaballoAlfil(xBlancas[5],yBlancas[5]);
    resultado+=mapa.pesoReina(xBlancas[6],yBlancas[6]);
    resultado+=mapa.pesoRey(xBlancas[7],yBlancas[7]);

    for (int var = 0; var < 4; var++) {
        resultado-=mapa.pesoPeon(xNegras[var],yNegras[var]);
    }
    resultado-=mapa.pesoCaballoAlfil(xNegras[4],yNegras[4]);
    resultado-=mapa.pesoCaballoAlfil(xNegras[5],yNegras[5]);
    resultado-=mapa.pesoReina(xNegras[6],yNegras[6]);
    resultado-=mapa.pesoRey(xNegras[7],yNegras[7]);

    delete xBlancas;
    delete yBlancas;
    delete xNegras;
    delete yNegras;

    return resultado;
}

QList<Nodo*> MiniMax::expandir(Nodo *elNodo)
{
    QList<Nodo*> respuesta;
    char** estadoTmp;
    int *posBlancasXTmp;
    int *posBlancasYTmp;
    int *posNegrasXTmp;
    int *posNegrasYTmp;
    string quienSoyTmp;
    bool color;

    int mover=0, idx=0, count=0, val=0;

    for (int i = 0; i < 8; i++) {//Intentar mover todas las fichas
        //los datos del padre
        estadoTmp=elNodo->getEstado();
        posBlancasXTmp=elNodo->getPosBlancasX();
        posBlancasYTmp=elNodo->getPosBlancasY();
        posNegrasXTmp=elNodo->getPosNegrasX();
        posNegrasYTmp=elNodo->getPosNegrasY();
        quienSoyTmp=i;

        if(elNodo->getNivel()%2==0) //blancas
        {
            if(i<4) //peones
            {
                //De ultimos... cuando se arregle sePuedeMover
            }
            else if(i==4) //Caballo
            {
                for (int j = 0; j < 8; j++)
                {
                    //Recuperar los datos del padre
                    estadoTmp=elNodo->getEstado();
                    posBlancasXTmp=elNodo->getPosBlancasX();
                    posBlancasYTmp=elNodo->getPosBlancasY();
                    posNegrasXTmp=elNodo->getPosNegrasX();
                    posNegrasYTmp=elNodo->getPosNegrasY();
                    quienSoyTmp=i;

                    val=sePuedeMover(posBlancasXTmp[i]+mapa.getDxCaballo(j),posBlancasYTmp[i]+mapa.getDyCaballo(j),i,true);
                    if(val!=-2)
                    {
                        estadoTmp[posBlancasXTmp[i]][posBlancasYTmp[i]]=' ';
                        estadoTmp[posBlancasXTmp[i]+mapa.getDxCaballo(j)][posBlancasYTmp[i]+mapa.getDyCaballo(j)]=mapa.getBlanca(i);
                        posBlancasXTmp[i]+=mapa.getDxCaballo(j);
                        posBlancasYTmp[i]+=mapa.getDyCaballo(j);

                        if(val!=-1)
                        {
                            posNegrasXTmp[val]=-1;
                            posNegrasYTmp[val]=-1;
                        }

                        quienSoyTmp+=posBlancasXTmp[i];
                        quienSoyTmp+=posBlancasYTmp[i];
                        respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasXTmp,posBlancasYTmp,posNegrasXTmp,posNegrasYTmp,estadoTmp,quienSoyTmp));
                    }
                }
            }
        }
        else //negras
        {

        }
    }

    return respuesta;
}

string MiniMax::tomarDesicion()
{
    Nodo *inicial=new Nodo(0,0,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,"original");

    //Inicia expandiendo el nodo
    QStack<Nodo*> plia;//Para expandirlos.
    QVector<Nodo*> vector;//para después eliminarlos

    QList<Nodo*> hijos;//donde se colocan los hijos generados



    return inicial->getDecision();
}

void MiniMax::definirVariables(char **estadoIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn)
{
    estado=estadoIn;
    posBlancasX=posBlancasXIn;
    posBlancasY=posBlancasYIn;
    posNegrasX=posNegrasXIn;
    posNegrasY=posNegrasYIn;
}

/*color=false => negras
  color=true => blancas

  Fichas= 0-3:peones 4:caballo 5:alfil 6:reina 7:rey

  Salida=   -2: No se puede mover (o se sale del tablero, o la casilla ocupada)
            -1: Casilla libre
             #: Ficha que se come
*/
int MiniMax::sePuedeMover(int xDestino, int yDestino, int ficha, bool color)
{
    if(xDestino<0 || xDestino>5 || yDestino<0 || yDestino>5) return -2;

    /*No sirve
    //Verificar Peones
    if(ficha<4 && color) //Peones Blancos
    {
        if(xDestino==posBlancasX[ficha] && yDestino==(posBlancasY[ficha]-1))
        {
            if(estado[xDestino][yDestino]==' ') return -1;
            else return -2;
        }
        else
        {
            if(estado[xDestino][yDestino]==' ' ||  estado[xDestino][yDestino]<82) return -2;
            else return estado[xDestino][yDestino];
        }
    }
    else if(ficha<4 && !color) //Peones Negros
    {
        if(xDestino==posNegrasX[ficha] && yDestino==(posNegrasY[ficha]+1))
        {
            if(estado[xDestino][yDestino]==' ') return -1;
            else return -2;
        }
        else
        {
            if(estado[xDestino][yDestino]==' ' ||  estado[xDestino][yDestino]>97) return -2;
            else return estado[xDestino][yDestino];
        }
    }
    else //Verificar Resto
    {*/
        if (color)
        {
            if(estado[xDestino][yDestino]==' ') return -1;
            else if( estado[xDestino][yDestino]<82) return -2;
            else return estado[xDestino][yDestino];
        }
        else
        {
            if(estado[xDestino][yDestino]==' ') return -1;
            else if( estado[xDestino][yDestino]>97) return -2;
            else return estado[xDestino][yDestino];
        }
//    }
}

/*
    B = 66    b = 98
    C = 67    c = 99
    K = 75    k = 107
    P = 80    p = 112
    Q = 81    q = 113

    color=false => negras / color=true => blancas

 */
bool MiniMax::verificarJaque(bool color)
{

    int delta = color? 32 : 0;

    int reyX = color? posBlancasX[7] : posNegrasX[7];
    int reyY = color? posBlancasY[7] : posNegrasY[7];

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

        xx = reyX+(count*mapa.getDxDiago(idx));
        yy = reyY+(count*mapa.getDyDiago(idx));

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

        xx = reyX+(count*mapa.getDxRectas(idx));
        yy = reyY+(count*mapa.getDyRectas(idx));

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
        xx = reyX + mapa.getDxCaballo(i);
        yy = reyY + mapa.getDyCaballo(i);

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
        xx = reyX + mapa.getDxRey(i);
        yy = reyY + mapa.getDyRey(i);

        if(xx<0 || xx>5 || yy<0 || yy>5)
            continue;
        else
            if(estado[yy][xx] == (75+delta))
                return true;
    }

    return respuesta;
}

