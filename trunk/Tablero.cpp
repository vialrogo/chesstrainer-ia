#include "Tablero.h"

Tablero::Tablero()
{

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animar()));
}

void Tablero::crearCuadros()
{
//    int anchoCelda = (W/M);
//    int altoCelda = (H/N);

//    imagenesFicha = new  Ficha*[CantidadCarros];
//    bool* pintado = new bool[CantidadCarros];

//    for (int i = 0; i < CantidadCarros; ++i)
//    {
//        //carros[i] = new imagencarro();
//        pintado[i]=false;
//    }

//    int tmp=0;
//    char letra=' ';
//    char orientacion=' ';

//    for (int i = 0; i < N; ++i)
//    {
//        for (int j = 0; j < M; ++j)
//        {
//            letra = (matriz[i][j]);
//            tmp =  letra - 65;

//            if(letra != '0' && letra!='1' && !pintado[tmp])
//            {
//                pintado[tmp]=true;

//                if(direcciones[tmp])
//                    orientacion='2';
//                else
//                    orientacion='1';

//                QString ruta = QString("Imagenes/%1%2.png").arg(letra).arg(orientacion);
//                carros[tmp]= new imagencarro(QSizeF(65*7,65*7),QPixmap (ruta),this);
//                carros[tmp]->setOffset (j*anchoCelda,i*altoCelda);
//                posicionesCarro[tmp]= QPoint(0,0);
//                this->addItem(carros[tmp]);
//            }

//            if(letra == '1')
//            {
//                QGraphicsRectItem* qri =  new QGraphicsRectItem(j*anchoCelda,i*altoCelda,anchoCelda,altoCelda);
//                qri->setBrush(QPixmap ("Imagenes/muro.jpg"));
//                qri->setPen(QColor(180,180,180,0));
//                this->addItem(qri);
//            }
//        }
//    }
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
