#include "Tablero.h"

Tablero::Tablero()
{
    //Variables globales
    deltaX=30+1; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    deltaY=30+1; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    anchoCelda = 80; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    altoCelda = 80; //Quemados en el código!! se definen en Ventana::pintarCuadricula()

    xSelected=-1;
    ySelected=-1;

    //Inicializo la matriz de cuadros
    matrizCuadrados = new QGraphicsRectItem**[6];
    for (int i = 0; i < 6; ++i)
        matrizCuadrados[i] = new QGraphicsRectItem*[6];

    //Timer para las animaciones
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animar()));
}

void Tablero::crearFichas(int *posBlancasX, int *posBlancasY, int *posNegrasX, int *posNegrasY)
{
    imagenesFichasBlancas = new  Ficha*[8];
    imagenesFichasNegras = new  Ficha*[8];

    for (int i = 0; i < 8; ++i)
    {
        if(i<4) //Peones
        {
            imagenesFichasBlancas[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/P.png"),this);
            imagenesFichasNegras[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/p.png"),this);
        }

        if(i==4) //Caballo
        {
            imagenesFichasBlancas[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/C.png"),this);
            imagenesFichasNegras[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/c.png"),this);
        }

        if(i==5) //Alfil
        {
            imagenesFichasBlancas[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/B.png"),this);
            imagenesFichasNegras[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/b.png"),this);
        }

        if(i==6) //Reina
        {
            imagenesFichasBlancas[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/Q.png"),this);
            imagenesFichasNegras[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/q.png"),this);
        }

        if(i==7) //Rey
        {
            imagenesFichasBlancas[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/K.png"),this);
            imagenesFichasNegras[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/k.png"),this);
        }

        imagenesFichasBlancas[i]->setOffset(posBlancasX[i]*anchoCelda+deltaX,posBlancasY[i]*altoCelda+deltaY);
        this->addItem(imagenesFichasBlancas[i]);

        imagenesFichasNegras[i]->setOffset(posNegrasX[i]*anchoCelda+deltaX,posNegrasY[i]*altoCelda+deltaY);
        this->addItem(imagenesFichasNegras[i]);
    }
}

void Tablero::mousePressEvent(QGraphicsSceneMouseEvent* mouseevent)
{
    //Se optiene la posición donde se dio clic
    QPointF posicion = mouseevent->scenePos();
    double xpos = posicion.rx();
    double ypos = posicion.ry();

    //Con esto se sale si se ha dado clic fuera del tablero
    if(xpos<=deltaX || ypos<=deltaY || xpos>=480+deltaX || ypos>=480+deltaY) return;

    //Se calcula la celda donde se dió clic
    int xCelda = (xpos-deltaX)/anchoCelda;
    int yCelda = (ypos-deltaY)/altoCelda;

    if(estado[yCelda][xCelda]!=' ')
    {
        if(xSelected==-1 && ySelected==-1) //No hay ninguna ficha seleccionada
        {
            matrizCuadrados[yCelda][xCelda]->setBrush(QColor(0,0,180,255));
            xSelected=xCelda;
            ySelected=yCelda;
        }
        else
        {
            if(xSelected==xCelda && ySelected==yCelda) //Se volvió a cliclear en la ficha seleccionada
            {
                if((xCelda+yCelda)%2==0)
                    matrizCuadrados[yCelda][xCelda]->setBrush(QColor(255,255,255,255));
                else
                    matrizCuadrados[yCelda][xCelda]->setBrush(QColor(0,0,0,255));

                xSelected=-1;
                ySelected=-1;
            }
            else //Se cliqueo en una ficha, cuando ya había OTRA seleccionada
            {
                matrizCuadrados[yCelda][xCelda]->setBrush(QColor(0,0,180,255));

                if((xSelected+ySelected)%2==0)
                    matrizCuadrados[ySelected][xSelected]->setBrush(QColor(255,255,255,255));
                else
                    matrizCuadrados[ySelected][xSelected]->setBrush(QColor(0,0,0,255));

                xSelected=xCelda;
                ySelected=yCelda;
            }

        }
    }
}

void Tablero::animar()
{
//    if(0 == solucion.size() && 0 == tiempo )
//    {
//        timer->stop();
//        emit terminoAnimacion();
//    }
//    else
//    {
//        if(0 == tiempo)
//        {
//            QString l = solucion.left(3);
//            QString tmp;
//            solucion = solucion.right(solucion.size()-3);
//            tmp = l.left(1);
//            l = l.right(2);
//            carroActual = tmp.toLocal8Bit().data()[0];
//            tmp = l.left(1);
//            l = l.right(1);
//            dirreccionActual = tmp.toInt();
//            tiempo = l.toInt()-1;
//            moverCarro(carroActual,dirreccionActual);
//        }
//        else
//        {
//            tiempo--;
//            moverCarro(carroActual,dirreccionActual);
//        }
//    }
}

void Tablero::moverFicha(/*char carro, int direccion*/)
{
//    int anchoCelda = (W/M);
//    int altoCelda = (H/N);
//    int NumeroCarro = (carro - 65);
//    int posX = posicionesCarro[NumeroCarro].rx();
//    int posY = posicionesCarro[NumeroCarro].ry();

////    cout<<"posX: "<<posX<<" posY: "<<posY<<endl;

//    if(direcciones[NumeroCarro]) //Movimiento vertical
//    {
//        if(direccion==1) //Moverse hacia arriba
//        {
//           carros[NumeroCarro]->animatePosition(QPointF( posX, (-1*altoCelda) + posY) );
//           posicionesCarro[NumeroCarro].setY( (-1*altoCelda) + posY );
//        }
//        else //Moverse hacia abajo
//        {
//           carros[NumeroCarro]->animatePosition(QPointF( posX, altoCelda+posY) );
//           posicionesCarro[NumeroCarro].setY( altoCelda + posY );
//        }
//    }
//    else //Movimiento horizontal
//    {
//        if(direccion==1) //Moverse hacia la derecha
//        {
//            carros[NumeroCarro]->animatePosition(QPointF( posX + anchoCelda, posY));
//            posicionesCarro[NumeroCarro].setX( anchoCelda + posX);
//        }
//        else //Moverse hacia la izquierda
//        {
//            carros[NumeroCarro]->animatePosition(QPointF( posX + (-1*anchoCelda), posY ) );
//            posicionesCarro[NumeroCarro].setX( (-1*anchoCelda) + posX );
//        }
//    }
}


void Tablero::pintarCuadricula()
{
    clear();

    //Cuadros
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            matrizCuadrados[j][i] = new QGraphicsRectItem(i*altoCelda+deltaY,j*anchoCelda+deltaX,anchoCelda,altoCelda,0,this);
            matrizCuadrados[j][i]->setPen(QColor(180,180,180,255));//Color de linea

            if((i+j)%2==0)
                matrizCuadrados[j][i]->setBrush(QColor(255,255,255,255));//Cuadros Blancos
            else
                matrizCuadrados[j][i]->setBrush(QColor(0,0,0,255));//Cuadros Negros
        }
    }

    //Texto
    QString letras[6] = {"a","b","c","d","e","f"};
    QString numeros[6] = {"1","2","3","4","5","6"};
    QFont fuente("Times", 12, QFont::Monospace);
    int dxnumeros=5;
    int dyletras=4;

    for (int i = 0; i < 6; ++i)
    {
        QGraphicsTextItem* letraSuperior = new QGraphicsTextItem(letras[i],0,this);
        letraSuperior->setFont(fuente);
        letraSuperior->setPos(deltaX+40+(i*80),dyletras);
        QGraphicsTextItem* letraInferior = new QGraphicsTextItem(letras[i],0,this);
        letraInferior->setFont(fuente);
        letraInferior->setPos(deltaX+40+(i*80),deltaY+480+dyletras);
        QGraphicsTextItem* numeroSuperior = new QGraphicsTextItem(numeros[i],0,this);
        numeroSuperior->setFont(fuente);
        numeroSuperior->setPos(dxnumeros,deltaY+40+(i*80));
        QGraphicsTextItem* numeroInferior = new QGraphicsTextItem(numeros[i],0,this);
        numeroInferior->setFont(fuente);
        numeroInferior->setPos(deltaX+480+dxnumeros,deltaY+40+(i*80));
    }

}

void Tablero::pararAnimacion()
{
    timer->stop();
}

void Tablero::setEstado(char ** estado_in)
{
    estado=estado_in;
}
