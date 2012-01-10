#include "Tablero.h"

Tablero::Tablero()
{

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animar()));
}

void Tablero::crearCuadros(int *posBlancasX, int *posBlancasY, int *posNegrasX, int *posNegrasY)
{
    int deltax=30+1; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    int deltay=30+1; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    int anchoCelda = 80; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    int altoCelda = 80; //Quemados en el código!! se definen en Ventana::pintarCuadricula()

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

        imagenesFichasBlancas[i]->setOffset(posBlancasX[i]*anchoCelda+deltax,posBlancasY[i]*altoCelda+deltay);
        this->addItem(imagenesFichasBlancas[i]);

        imagenesFichasNegras[i]->setOffset(posNegrasX[i]*anchoCelda+deltax,posNegrasY[i]*altoCelda+deltay);
        this->addItem(imagenesFichasNegras[i]);
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

void Tablero::pararAnimacion()
{
    timer->stop();
}
