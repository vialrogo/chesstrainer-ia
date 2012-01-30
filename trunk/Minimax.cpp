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
        resultado+=mapa.pesoPeonBlanco(xBlancas[var],yBlancas[var]);
    }
    resultado+=mapa.pesoCaballoAlfil(xBlancas[4],yBlancas[4]);
    resultado+=mapa.pesoCaballoAlfil(xBlancas[5],yBlancas[5]);
    resultado+=mapa.pesoReina(xBlancas[6],yBlancas[6]);
    resultado+=mapa.pesoRey(xBlancas[7],yBlancas[7]);

    for (int var = 0; var < 4; var++) {
        resultado-=mapa.pesoPeonNegro(xNegras[var],yNegras[var]);
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

void MiniMax::imprimir(Nodo *elNodo)
{
    cout<<elNodo->getQuiensoy()<<endl;
    //Para imprimir la matriz
    for (int i = 0; i < 6; ++i) {
        cout<<"+---+---+---+---+---+---+"<<endl;
        for (int j = 0; j < 6; ++j) {
            cout<<"| "<<elNodo->getEstado()[i][j]<<" ";
        }
        cout<<"|"<<endl;
    }
    cout<<"+---+---+---+---+---+---+"<<endl<<endl;

    //Para imprimir los arreglos
    cout<<"+-------+---+---+---+---+---+---+---+---+"<<endl;
    cout<<"| Color | A | B | C | D | E | F | G | H |"<<endl;
    cout<<"+-------+---+---+---+---+---+---+---+---+"<<endl;
    cout<<"|Blanco |";
    for (int i = 0; i < 8; ++i)
    {
        if(elNodo->getPosBlancasX()[i]==-1) cout<<" -";
        else cout<<elNodo->getPosBlancasX()[i]<<",";

        if(elNodo->getPosBlancasY()[i]==-1) cout<<" |";
        else cout<<elNodo->getPosBlancasY()[i]<<"|";
    }
    cout<<endl;
    cout<<"+-------+---+---+---+---+---+---+---+---+"<<endl;
    cout<<"|Negro  |";
    for (int i = 0; i < 8; ++i)
    {
        if(elNodo->getPosNegrasX()[i]==-1) cout<<" -";
        else cout<<elNodo->getPosNegrasX()[i]<<",";

        if(elNodo->getPosNegrasY()[i]==-1) cout<<" |";
        else cout<<elNodo->getPosNegrasY()[i]<<"|";
    }
    cout<<endl;
    cout<<"+-------+---+---+---+---+---+---+---+---+"<<endl<<endl;
}

void MiniMax::imprimir(char **estadoIn)
{
    //Para imprimir la matriz
    for (int i = 0; i < 6; ++i) {
        cout<<"+---+---+---+---+---+---+"<<endl;
        for (int j = 0; j < 6; ++j) {
            cout<<"| "<<estadoIn[i][j]<<" ";
        }
        cout<<"|"<<endl;
    }
    cout<<"+---+---+---+---+---+---+"<<endl<<endl;
}

QList<Nodo*> MiniMax::expandir(Nodo *elNodo)
{    
    QList<Nodo*> respuesta;

    //La información del padre será almacenada en las variables de la clase
    string quienSoy="";

    int count=0, val=0, dx=0, dy=0;

    for (int i = 0; i < 8; i++){//Intentar mover todas las fichas
        definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),false);

        if(elNodo->getNivel()%2==0) //blancas
        {
            if(posBlancasX[i]!=-1 && posBlancasY[i]!=-1)
            {
                if(i<4) //peones
                {

                    //Mover hacia arriba
                    //Recuperar los datos del padre
                    definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
                    stringstream quienSoyTmp1;

                    val=sePuedeMover(posBlancasX[i]-1,posBlancasY[i],i,true);
                    if(val==-1)
                    {
                        estado[posBlancasX[i]][posBlancasY[i]]=' ';
                        estado[posBlancasX[i]-1][posBlancasY[i]]=mapa.getBlanca(i);
                        posBlancasX[i]=posBlancasX[i]-1;
                        quienSoyTmp1<<i;
                        quienSoyTmp1<<posBlancasX[i];
                        quienSoyTmp1<<posBlancasY[i];
                        quienSoy=quienSoyTmp1.str();
                        respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                    }

                    //Mover diagonal arriba izquierda
                    //Recuperar los datos del padre
                    definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
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
                    definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
                    stringstream quienSoyTmp3;

                    val=sePuedeMover(posBlancasX[i]-1,posBlancasY[i]+1,i,true);
                    if(val!=-2)
                    {
                        estado[posBlancasX[i]][posBlancasY[i]]=' ';
                        estado[posBlancasX[i]-1][posBlancasY[i]+1]=mapa.getBlanca(i);
                        posBlancasX[i]=posBlancasX[i]-1;
                        posBlancasY[i]=posBlancasY[i]+1;

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
                        definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
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
                    for (int j = 0; j < 4; j++)
                    {
                        count=1;
                        do
                        {
                            //Recuperar los datos del padre
                            definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
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
                                definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
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
                        definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
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
        }
        else //negras
        {
            if(posNegrasX[i]!=-1 && posNegrasY[i]!=-1)
            {
                if(i<4) //peones
                {
                    //Mover hacia abajo
                    //Recuperar los datos del padre
                    definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
                    stringstream quienSoyTmp1;

                    val=sePuedeMover(posNegrasX[i]+1,posNegrasY[i],i,false);
                    if(val==-1)
                    {
                        estado[posNegrasX[i]][posNegrasY[i]]=' ';
                        estado[posNegrasX[i]+1][posNegrasY[i]]=mapa.getNegra(i);
                        posNegrasX[i]=posNegrasX[i]+1;
                        quienSoyTmp1<<i;
                        quienSoyTmp1<<posNegrasX[i];
                        quienSoyTmp1<<posNegrasY[i];
                        quienSoy=quienSoyTmp1.str();
                        respuesta.push_back(new Nodo(elNodo,elNodo->getNivel()+1,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,quienSoy));
                    }

                    //Mover diagonal abajo izquierda
                    //Recuperar los datos del padre
                    definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
                    stringstream quienSoyTmp2;

                    val=sePuedeMover(posNegrasX[i]+1,posNegrasY[i]-1,i,false);
                    if(val!=-2)
                    {
                        estado[posNegrasX[i]][posNegrasY[i]]=' ';
                        estado[posNegrasX[i]+1][posNegrasY[i]-1]=mapa.getNegra(i);
                        posNegrasX[i]=posNegrasX[i]+1;
                        posNegrasY[i]=posNegrasY[i]-1;

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
                    definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
                    stringstream quienSoyTmp3;

                    val=sePuedeMover(posNegrasX[i]+1,posNegrasY[i]+1,i,false);
                    if(val!=-2)
                    {
                        estado[posNegrasX[i]][posNegrasY[i]]=' ';
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
                        definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
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
                            definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
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
                                definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
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
                else if(i==7) //Rey
                {
                    for (int j = 0; j < 8; j++)
                    {
                        //Recuperar los datos del padre
                        definirVariables(elNodo->getEstado(),elNodo->getPosBlancasX(),elNodo->getPosBlancasY(),elNodo->getPosNegrasX(),elNodo->getPosNegrasY(),true);
                        stringstream quienSoyTmp;

                        val=sePuedeMover(posNegrasX[i]+mapa.getDxRey(j),posNegrasY[i]+mapa.getDyRey(j),i,false);
                        if(val!=-2)
                        {
                            estado[posNegrasX[i]][posNegrasY[i]]=' ';
                            estado[posNegrasX[i]+mapa.getDxRey(j)][posNegrasY[i]+mapa.getDyRey(j)]=mapa.getNegra(i);
                            posNegrasX[i]+=mapa.getDxRey(j);
                            posNegrasY[i]+=mapa.getDyRey(j);

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
            }
        }
    }

    return respuesta;
}

string MiniMax::tomarDesicion()
{
    Nodo *inicial=new Nodo(0,0,posBlancasX,posBlancasY,posNegrasX,posNegrasY,estado,"original");
    imprimir(inicial);
    Nodo *actual;
    int heuristicaTmp=0;
    string decision="";

    //Inicia expandiendo el nodo
    QStack<Nodo*> pila;//Para expandirlos.
    QList<Nodo*> aBorrar;//para después eliminarlos
    QList<Nodo*> hijos;//donde se colocan los hijos generados

    pila.push_front(inicial);

    while (!pila.isEmpty()) {
        actual=pila.front();
        pila.pop_front();

        if(actual->getNivel()==nivel)
        {
            heuristicaTmp=calcularHeuristica(actual);
            actual->actualizarDesicion(heuristicaTmp,actual->getQuiensoy());
        }
        else
        {
            hijos=expandir(actual);
            while (!hijos.isEmpty()) {
                pila.push_front(hijos.back());
                hijos.pop_back();
            }
        }
        aBorrar.push_front(actual);
    }
    hijos.clear();

    for (int i = 0; i < aBorrar.size(); i++) {
        actual=aBorrar.at(i);
        if(actual->getPadre()!=0)
            actual->getPadre()->actualizarDesicion(actual->getValor(),actual->getQuiensoy());
    }

    decision=inicial->getDecision();
//    definirVariables(inicial->getEstado(),inicial->getPosBlancasX(),inicial->getPosBlancasY(),inicial->getPosNegrasX(),inicial->getPosNegrasY(),false);

    while(!aBorrar.isEmpty()){
        actual=aBorrar.front();
        aBorrar.pop_front();
        delete actual;
    }

    return decision;
}

void MiniMax::definirVariables(char **estadoIn, int *posBlancasXIn, int *posBlancasYIn, int *posNegrasXIn, int *posNegrasYIn, bool copia)
{
    if(copia)
    {
        estado=new char*[6];
        for (int i = 0; i < 6; i++) {
            estado[i]=new char[6];
        }
        posBlancasX=new int[8];
        posBlancasY=new int[8];
        posNegrasX=new int[8];
        posNegrasY=new int[8];

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
    else
    {
        estado=estadoIn;
        posBlancasX=posBlancasXIn;
        posBlancasY=posBlancasYIn;
        posNegrasX=posNegrasXIn;
        posNegrasY=posNegrasYIn;
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
        if(xDestino==posBlancasX[ficha]-1 && yDestino==(posBlancasY[ficha]))
        {
            if(estado[xDestino][yDestino]==' ') return -1;
            else return -2;
        }
        else
        {
            if(estado[xDestino][yDestino]==' ' ||  estado[xDestino][yDestino]<73) return -2;
            else return estado[xDestino][yDestino]-97;
        }
    }
    else if(ficha<4 && !color) //Peones Negros
    {
        if(xDestino==posNegrasX[ficha]+1 && yDestino==(posNegrasY[ficha]))
        {
            if(estado[xDestino][yDestino]==' ') return -1;
            else return -2;
        }
        else
        {
            if(estado[xDestino][yDestino]==' ' ||  estado[xDestino][yDestino]>96) return -2;
            else return estado[xDestino][yDestino]-65;
        }
    }
    else //Verificar Resto
    {
        if (color)
        {
            if(estado[xDestino][yDestino]==' ') return -1;
            else if( estado[xDestino][yDestino]<73) return -2;
            else return estado[xDestino][yDestino]-97;
        }
        else
        {
            if(estado[xDestino][yDestino]==' ') return -1;
            else if( estado[xDestino][yDestino]>96) return -2;
            else return estado[xDestino][yDestino]-65;
        }
    }
}

/*
    A=65
    H=72
    a=97
    h=104

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
            if(estado[xx][yy] == ' ')
                count++;
            else{
                if(estado[xx][yy] == (70+delta) || estado[xx][yy] == (71+delta))
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
            if(estado[xx][yy] == ' ')
                count++;
            else{
                if(estado[xx][yy] == (71+delta))
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
            if(estado[xx][yy] == (69+delta))
                return true;
    }

    //Peones
    if(color)
    {
        if(reyX>0 && reyY>0)
            if(estado[reyX-1][reyY-1]>96 && estado[reyX-1][reyY-1]<101)
                return true;

        if(reyX>0 && reyY<5)
            if(estado[reyX-1][reyY+1]>96 && estado[reyX-1][reyY+1]<101)
                return true;
    }
    else
    {
        if(reyX<5 && reyY>0)
            if(estado[reyX+1][reyY-1]<69 && estado[reyX+1][reyY-1]>64)
                return true;

        if(reyX<5 && reyY<5)
            if(estado[reyX+1][reyY+1]<69 && estado[reyX+1][reyY+1]>64)
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
            if(estado[xx][yy] == (72+delta))
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

//    blancasX[0]=1; blancasX[1]=1; blancasX[2]=2; blancasX[3]=3; blancasX[4]=0; blancasX[5]=1; blancasX[6]=0; blancasX[7]=3;
//    blancasY[0]=2; blancasY[1]=1; blancasY[2]=1; blancasY[3]=1; blancasY[4]=0; blancasY[5]=0; blancasY[6]=1; blancasY[7]=2;

//    negrasX[0]=0; negrasX[1]=1; negrasX[2]=2; negrasX[3]=3; negrasX[4]=0; negrasX[5]=1; negrasX[6]=4; negrasX[7]=5;
//    negrasY[0]=5; negrasY[1]=5; negrasY[2]=5; negrasY[3]=5; negrasY[4]=2; negrasY[5]=3; negrasY[6]=4; negrasY[7]=5;

//    blancasX[0]=3; blancasX[1]=3; blancasX[2]=4; blancasX[3]=5; blancasX[4]=5; blancasX[5]=5; blancasX[6]=4; blancasX[7]=4;
//    blancasY[0]=4; blancasY[1]=5; blancasY[2]=3; blancasY[3]=0; blancasY[4]=5; blancasY[5]=4; blancasY[6]=5; blancasY[7]=4;

//    negrasX[0]=1; negrasX[1]=4; negrasX[2]=0; negrasX[3]=2; negrasX[4]=3; negrasX[5]=1; negrasX[6]=0; negrasX[7]=0;
//    negrasY[0]=1; negrasY[1]=2; negrasY[2]=2; negrasY[3]=1; negrasY[4]=3; negrasY[5]=0; negrasY[6]=0; negrasY[7]=1;

    blancasX[0]=-1; blancasX[1]=0; blancasX[2]=2; blancasX[3]=5; blancasX[4]=4; blancasX[5]=-1; blancasX[6]=-1; blancasX[7]=5;
    blancasY[0]=-1; blancasY[1]=3; blancasY[2]=4; blancasY[3]=5; blancasY[4]=5; blancasY[5]=-1; blancasY[6]=-1; blancasY[7]=4;

    negrasX[0]=2; negrasX[1]=4; negrasX[2]=5; negrasX[3]=3; negrasX[4]=-1; negrasX[5]=1; negrasX[6]=-1; negrasX[7]=3;
    negrasY[0]=2; negrasY[1]=0; negrasY[2]=1; negrasY[3]=1; negrasY[4]=-1; negrasY[5]=0; negrasY[6]=-1; negrasY[7]=0;

    for (int i = 0; i < 8; i++)
    {
        if(blancasY[i]!=-1 && blancasX[i]!=-1)
        {
            est[blancasY[i]][blancasX[i]]=(i+65);
        }
        if(negrasY[i]!=-1 && negrasX[i]!=-1)
        {
            est[negrasY[i]][negrasX[i]]=(i+97);
        }
    }

    MiniMax obj(2);
    obj.definirVariables(est,blancasY,blancasX,negrasY,negrasX,true);
    obj.tomarDesicion();
}
*/
