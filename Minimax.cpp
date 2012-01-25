#include "Minimax.h"

MiniMax::MiniMax(int nivelIn)
{
    nivel=nivelIn;//2=principiante, 4=amateur
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
    //La información del padre será almacenada en las variables de la clase

    string quienSoy="";

    int count=0, val=0, dx=0, dy=0;

    for (int i = 0; i < 8; i++) {//Intentar mover todas las fichas

        if(elNodo->getNivel()%2==0) //blancas
        {
            if(i<4) //peones
            {

                //Mover hacia arriba
                //Recuperar los datos del padre
                definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                stringstream quienSoyTmp1;

                val=sePuedeMover(posBlancasX[i],posBlancasY[i]-1,i,true);
                if(val==-1)
                {
                    estado[posBlancasX[i]][posBlancasY[i]]=' ';
                    estado[posBlancasX[i]][posBlancasY[i]-1]=mapa.getBlanca(i);
                    posBlancasY[i]=posBlancasY[i]-1;
                    quienSoyTmp1<<i;
                    quienSoyTmp1<<posBlancasX[i];
                    quienSoyTmp1<<posBlancasY[i];
                    quienSoy=quienSoyTmp1.str();
                    respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                }

                //Mover diagonal arriba izquierda
                //Recuperar los datos del padre
                definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                stringstream quienSoyTmp2;

                val=sePuedeMover(posBlancasX[i]-1,posBlancasY[i]-1,i,true);
                if(val!=-2)
                {
                    estado[posBlancasX[i]][posBlancasY[i]]=' ';
                    estado[posBlancasX[i]-1][posBlancasY[i]-1]=mapa.getBlanca(i);
                    posBlancasX[i]=posBlancasX[i]-1;
                    posBlancasY[i]=posBlancasY[i]-1;

                    posNegrasX[val]=-1;
                    posNegrasY[val]=-1;
                    quienSoyTmp2<<i;
                    quienSoyTmp2<<posBlancasX[i];
                    quienSoyTmp2<<posBlancasY[i];
                    quienSoy=quienSoyTmp2.str();
                    respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                }

                //Mover diagonal arriba derecha
                //Recuperar los datos del padre
                definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                stringstream quienSoyTmp3;

                val=sePuedeMover(posBlancasX[i]+1,posBlancasY[i]-1,i,true);
                if(val!=-2)
                {
                    estado[posBlancasX[i]][posBlancasY[i]]=' ';
                    estado[posBlancasX[i]+1][posBlancasY[i]-1]=mapa.getBlanca(i);
                    posBlancasX[i]=posBlancasX[i]+1;
                    posBlancasY[i]=posBlancasY[i]-1;

                    posNegrasX[val]=-1;
                    posNegrasY[val]=-1;
                    quienSoyTmp3<<i;
                    quienSoyTmp3<<posBlancasX[i];
                    quienSoyTmp3<<posBlancasY[i];
                    quienSoy=quienSoyTmp3.str();
                    respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                }
            }
            else if(i==4) //Caballo
            {
                for (int j = 0; j < 8; j++)
                {
                    //Recuperar los datos del padre
                    definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                    stringstream quienSoyTmp;

                    val=sePuedeMover(posBlancasX[i]+mapa.getDxCaballo(j),posBlancasY[i]+mapa.getDyCaballo(j),i,true);
                    if(val!=-2)
                    {
                        estado[posBlancasX[i]][posBlancasY[i]]=' ';
                        estado[posBlancasX[i]+mapa.getDxCaballo(j)][posBlancasY[i]+mapa.getDyCaballo(j)]=mapa.getBlanca(i);
                        posBlancasX[i]+=mapa.getDxCaballo(j);
                        posBlancasY[i]+=mapa.getDyCaballo(j);

                        if(val!=-1)
                        {
                            posNegrasX[val]=-1;
                            posNegrasY[val]=-1;
                        }

                        quienSoyTmp<<i;
                        quienSoyTmp<<posBlancasX[i];
                        quienSoyTmp<<posBlancasY[i];
                        quienSoy=quienSoyTmp.str();
                        respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                    }
                }
            }
            else if(i==5 || i==6) //Alfil o Reina (diagonales)
            {
                for (int j = 0; j < 4; ++j)
                {
                    count=1;
                    do
                    {
                        //Recuperar los datos del padre
                        definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                        stringstream quienSoyTmp;

                        dx=mapa.getDxDiago(j)*count;
                        dy=mapa.getDyDiago(j)*count;

                        val=sePuedeMover(posBlancasX[i]+dx,posBlancasY[i]+dy,i,true);

                        if(val!=-2)
                        {
                            estado[posBlancasX[i]][posBlancasY[i]]=' ';
                            estado[posBlancasX[i]+dx][posBlancasY[i]+dy]=mapa.getBlanca(i);
                            posBlancasX[i]+=dx;
                            posBlancasY[i]+=dy;

                            if(val!=-1)
                            {
                                posNegrasX[val]=-1;
                                posNegrasY[val]=-1;
                            }

                            quienSoyTmp<<i;
                            quienSoyTmp<<posBlancasX[i];
                            quienSoyTmp<<posBlancasY[i];
                            quienSoy=quienSoyTmp.str();
                            respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                        }
                        count++;
                    } while (val==-1);
                }
                if(i==6) //Reina (Rectas)
                {
                    for (int j = 0; j < 4; ++j)
                    {
                        count=1;
                        do
                        {
                            //Recuperar los datos del padre
                            definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                            stringstream quienSoyTmp;

                            dx=mapa.getDxRectas(j)*count;
                            dy=mapa.getDyRectas(j)*count;

                            val=sePuedeMover(posBlancasX[i]+dx,posBlancasY[i]+dy,i,true);

                            if(val!=-2)
                            {
                                estado[posBlancasX[i]][posBlancasY[i]]=' ';
                                estado[posBlancasX[i]+dx][posBlancasY[i]+dy]=mapa.getBlanca(i);
                                posBlancasX[i]+=dx;
                                posBlancasY[i]+=dy;

                                if(val!=-1)
                                {
                                    posNegrasX[val]=-1;
                                    posNegrasY[val]=-1;
                                }

                                quienSoyTmp<<i;
                                quienSoyTmp<<posBlancasX[i];
                                quienSoyTmp<<posBlancasY[i];
                                quienSoy=quienSoyTmp.str();
                                respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                            }
                            count++;
                        } while (val==-1);
                    }
                }
            }
            else if(i==7) //Rey
            {
                for (int j = 0; j < 8; j++)
                {
                    //Recuperar los datos del padre
                    definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                    stringstream quienSoyTmp;

                    val=sePuedeMover(posBlancasX[i]+mapa.getDxRey(j),posBlancasY[i]+mapa.getDyRey(j),i,true);
                    if(val!=-2)
                    {
                        estado[posBlancasX[i]][posBlancasY[i]]=' ';
                        estado[posBlancasX[i]+mapa.getDxRey(j)][posBlancasY[i]+mapa.getDyRey(j)]=mapa.getBlanca(i);
                        posBlancasX[i]+=mapa.getDxRey(j);
                        posBlancasY[i]+=mapa.getDyRey(j);

                        if(val!=-1)
                        {
                            posNegrasX[val]=-1;
                            posNegrasY[val]=-1;
                        }

                        quienSoyTmp<<i;
                        quienSoyTmp<<posBlancasX[i];
                        quienSoyTmp<<posBlancasY[i];
                        quienSoy=quienSoyTmp.str();
                        respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                    }
                }
            }
        }
        else //negras
        {
            if(i<4) //peones
            {
                //Mover hacia abajo
                //Recuperar los datos del padre
                definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                stringstream quienSoyTmp1;

                val=sePuedeMover(posNegrasX[i],posNegrasY[i]+1,i,false);
                if(val==-1)
                {
                    estado[posNegrasX[i]][posNegrasY[i]]=' ';
                    estado[posNegrasX[i]][posNegrasY[i]+1]=mapa.getNegra(i);
                    posNegrasY[i]=posNegrasY[i]+1;
                    quienSoyTmp1<<i;
                    quienSoyTmp1<<posNegrasX[i];
                    quienSoyTmp1<<posNegrasY[i];
                    quienSoy=quienSoyTmp1.str();
                    respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                }

                //Mover diagonal abajo izquierda
                //Recuperar los datos del padre
                definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                stringstream quienSoyTmp2;

                val=sePuedeMover(posNegrasX[i]-1,posNegrasY[i]+1,i,false);
                if(val!=-2)
                {
                    estado[posNegrasX[i]-1][posNegrasY[i]+1]=' ';
                    estado[posNegrasX[i]-1][posNegrasY[i]+1]=mapa.getNegra(i);
                    posNegrasX[i]=posNegrasX[i]-1;
                    posNegrasY[i]=posNegrasY[i]+1;

                    posBlancasX[val]=-1;
                    posBlancasY[val]=-1;
                    quienSoyTmp2<<i;
                    quienSoyTmp2<<posNegrasX[i];
                    quienSoyTmp2<<posNegrasY[i];
                    quienSoy=quienSoyTmp2.str();
                    respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                }

                //Mover diagonal abajo derecha
                //Recuperar los datos del padre
                definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                stringstream quienSoyTmp3;

                val=sePuedeMover(posNegrasX[i]+1,posNegrasY[i]+1,i,false);
                if(val!=-2)
                {
                    estado[posNegrasX[i]+1][posNegrasY[i]+1]=' ';
                    estado[posNegrasX[i]+1][posNegrasY[i]+1]=mapa.getNegra(i);
                    posNegrasX[i]=posNegrasX[i]+1;
                    posNegrasY[i]=posNegrasY[i]+1;

                    posBlancasX[val]=-1;
                    posBlancasY[val]=-1;
                    quienSoyTmp3<<i;
                    quienSoyTmp3<<posNegrasX[i];
                    quienSoyTmp3<<posNegrasY[i];
                    quienSoy=quienSoyTmp3.str();
                    respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                }
            }
            else if(i==4) //Caballo
            {
                for (int j = 0; j < 8; j++)
                {
                    //Recuperar los datos del padre
                    definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                    stringstream quienSoyTmp;

                    val=sePuedeMover(posNegrasX[i]+mapa.getDxCaballo(j),posNegrasY[i]+mapa.getDyCaballo(j),i,false);
                    if(val!=-2)
                    {
                        estado[posNegrasX[i]][posNegrasY[i]]=' ';
                        estado[posNegrasX[i]+mapa.getDxCaballo(j)][posNegrasY[i]+mapa.getDyCaballo(j)]=mapa.getNegra(i);
                        posNegrasX[i]+=mapa.getDxCaballo(j);
                        posNegrasY[i]+=mapa.getDyCaballo(j);

                        if(val!=-1)
                        {
                            posBlancasX[val]=-1;
                            posBlancasY[val]=-1;
                        }

                        quienSoyTmp<<i;
                        quienSoyTmp<<posNegrasX[i];
                        quienSoyTmp<<posNegrasY[i];
                        quienSoy=quienSoyTmp.str();
                        respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                    }
                }
            }
            else if(i==5 || i==6) //Alfil o Reina (diagonales)
            {
                for (int j = 0; j < 4; ++j)
                {
                    count=1;
                    do
                    {
                        //Recuperar los datos del padre
                        definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                        stringstream quienSoyTmp;

                        dx=mapa.getDxDiago(j)*count;
                        dy=mapa.getDyDiago(j)*count;

                        val=sePuedeMover(posNegrasX[i]+dx,posNegrasY[i]+dy,i,false);

                        if(val!=-2)
                        {
                            estado[posNegrasX[i]][posNegrasY[i]]=' ';
                            estado[posNegrasX[i]+dx][posNegrasY[i]+dy]=mapa.getNegra(i);
                            posNegrasX[i]+=dx;
                            posNegrasY[i]+=dy;

                            if(val!=-1)
                            {
                                posBlancasX[val]=-1;
                                posBlancasY[val]=-1;
                            }

                            quienSoyTmp<<i;
                            quienSoyTmp<<posNegrasX[i];
                            quienSoyTmp<<posNegrasY[i];
                            quienSoy=quienSoyTmp.str();
                            respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                        }
                        count++;
                    } while (val==-1);
                }
                if(i==6) //Reina (Rectas)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        count=1;
                        do
                        {
                            //Recuperar los datos del padre
                            definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
                            stringstream quienSoyTmp;

                            dx=mapa.getDxRectas(j)*count;
                            dy=mapa.getDyRectas(j)*count;

                            val=sePuedeMover(posNegrasX[i]+dx,posNegrasY[i]+dy,i,false);

                            if(val!=-2)
                            {
                                estado[posNegrasX[i]][posNegrasY[i]]=' ';
                                estado[posNegrasX[i]+dx][posNegrasY[i]+dy]=mapa.getNegra(i);
                                posNegrasX[i]+=dx;
                                posNegrasY[i]+=dy;

                                if(val!=-1)
                                {
                                    posBlancasX[val]=-1;
                                    posBlancasY[val]=-1;
                                }

                                quienSoyTmp<<i;
                                quienSoyTmp<<posNegrasX[i];
                                quienSoyTmp<<posNegrasY[i];
                                quienSoy=quienSoyTmp.str();
                                respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                            }
                            count++;
                        } while (val==-1);
                    }
                }
            }
//            else if(i==7) //Rey
//            {
//                for (int j = 0; j < 8; j++)
//                {
//                    //Recuperar los datos del padre
//                    definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY());
//                    stringstream quienSoyTmp;

//                    val=sePuedeMover(posNegrasX[i]+mapa.getDxRey(j),posNegrasY[i]+mapa.getDyRey(j),i,false);
//                    if(val!=-2)
//                    {
//                        estado[posNegrasX[i]][posNegrasY[i]]=' ';
//                        estado[posNegrasX[i]+mapa.getDxRey(j)][posNegrasY[i]+mapa.getDyRey(j)]=mapa.getNegra(i);
//                        posNegrasX[i]+=mapa.getDxRey(j);
//                        posNegrasY[i]+=mapa.getDyRey(j);

//                        if(val!=-1)
//                        {
//                            posBlancasX[val]=-1;
//                            posBlancasY[val]=-1;
//                        }

//                        quienSoyTmp<<i;
//                        quienSoyTmp<<posNegrasX[i];
//                        quienSoyTmp<<posNegrasY[i];
//                        quienSoy=quienSoyTmp.str();
//                        respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
//                    }
//                }
//            }
        }
    }

    return respuesta;
}

string MiniMax::tomarDesicion()
{
    Nodo *inicial=new Nodo(0,1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,"original");

    //Inicia expandiendo el nodo
    QStack<Nodo*> plia;//Para expandirlos.
    QVector<Nodo*> vector;//para después eliminarlos

    QList<Nodo*> hijos;//donde se colocan los hijos generados

    hijos=expandir(inicial);

    int idx=0; // VARG: cambié esta varible de i a idx porque tenía conflicto con el for

    while (!hijos.isEmpty()) {
        cout<<hijos.front()->getQuiensoy()<<endl;
        for (int i = 0; i < 6; ++i) {
            cout<<"+---+---+---+---+---+---+"<<endl;
            for (int j = 0; j < 6; ++j) {
                cout<<"| "<<hijos.front()->getEstado()[j][i]<<" ";
            }
            cout<<"|"<<endl;
        }
        cout<<"+---+---+---+---+---+---+"<<endl<<endl;
        hijos.removeFirst();
        idx++;
        cout<<idx<<endl;
    }

    cout<<"Y ESTO?"<<endl;

    return inicial->getDecision();
}

void MiniMax::definirVariables(char **estadoIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn)
{
    estado=new char*[6];
    for (int i = 0; i < 6; i++) {
        estado[i]=new char[6];
    }
    posBlancasX=new int[7];
    posBlancasY=new int[7];
    posNegrasX=new int[7];
    posNegrasY=new int[7];

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            estado[i][j]=estadoIn[i][j];
        }
    }
    for (int i = 0; i < 8; i++) {
        posBlancasX[i]=posBlancasXIn[i];
        posBlancasY[i]=posBlancasYIn[i];
        posNegrasX[i]=posNegrasXIn[i];
        posNegrasY[i]=posNegrasYIn[i];
    }
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
    {
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
    }
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

/*
int main()
{
    char **est=new char*[6];
    for (int i = 0; i < 6; i++) {
        est[i]=new char[6];
    }
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            est[i][j]=' ';
        }
    }

    int *blancasX = new int[8];
    int *blancasY = new int[8];
    int *negrasX = new int[8];
    int *negrasY = new int[8];

//    blancasX[0]=0; blancasX[1]=2; blancasX[2]=4; blancasX[3]=3; blancasX[4]=1; blancasX[5]=2; blancasX[6]=3; blancasX[7]=5;
//    blancasY[0]=4; blancasY[1]=4; blancasY[2]=4; blancasY[3]=2; blancasY[4]=1; blancasY[5]=2; blancasY[6]=3; blancasY[7]=4;

//    negrasX[0]=0; negrasX[1]=3; negrasX[2]=4; negrasX[3]=5; negrasX[4]=2; negrasX[5]=4; negrasX[6]=4; negrasX[7]=5;
//    negrasY[0]=3; negrasY[1]=1; negrasY[2]=1; negrasY[3]=3; negrasY[4]=5; negrasY[5]=2; negrasY[6]=0; negrasY[7]=0;

    negrasX[0]=0; negrasX[1]=2; negrasX[2]=4; negrasX[3]=3; negrasX[4]=1; negrasX[5]=2; negrasX[6]=3; negrasX[7]=5;
    negrasY[0]=4; negrasY[1]=4; negrasY[2]=4; negrasY[3]=2; negrasY[4]=1; negrasY[5]=2; negrasY[6]=3; negrasY[7]=4;

    blancasX[0]=0; blancasX[1]=3; blancasX[2]=4; blancasX[3]=5; blancasX[4]=2; blancasX[5]=4; blancasX[6]=4; blancasX[7]=5;
    blancasY[0]=3; blancasY[1]=1; blancasY[2]=1; blancasY[3]=3; blancasY[4]=5; blancasY[5]=2; blancasY[6]=0; blancasY[7]=0;

    for (int i = 0; i < 8; i++)
    {
        if(blancasY[i]!=-1 && blancasX[i]!=-1)
        {
            if(i<4) est[blancasX[i]][blancasY[i]]='P';
            if(i==4) est[blancasX[i]][blancasY[i]]='H';
            if(i==5) est[blancasX[i]][blancasY[i]]='B';
            if(i==6) est[blancasX[i]][blancasY[i]]='Q';
            if(i==7) est[blancasX[i]][blancasY[i]]='K';
        }
        if(negrasY[i]!=-1 && negrasX[i]!=-1)
        {
            if(i<4) est[negrasX[i]][negrasY[i]]='p';
            if(i==4) est[negrasX[i]][negrasY[i]]='h';
            if(i==5) est[negrasX[i]][negrasY[i]]='b';
            if(i==6) est[negrasX[i]][negrasY[i]]='q';
            if(i==7) est[negrasX[i]][negrasY[i]]='k';
        }
    }

    cout<<"original"<<endl<<endl;
    for (int i = 0; i < 6; ++i) {
        cout<<"+---+---+---+---+---+---+"<<endl;
        for (int j = 0; j < 6; ++j) {
            cout<<"| "<<est[j][i]<<" ";
        }
        cout<<"|"<<endl;
    }
    cout<<"+---+---+---+---+---+---+"<<endl<<endl;

    MiniMax obj(2);
    obj.definirVariables(est,blancasX,blancasY,negrasX,negrasY);
    obj.tomarDesicion();
    cout<<"ESTO SALE?"<<endl;
}*/
