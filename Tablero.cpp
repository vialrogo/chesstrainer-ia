#include "Tablero.h"

Tablero::Tablero()
{
    //Variables globales
    deltaX=31; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    deltaY=31; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    anchoCelda = 80; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    altoCelda = 80; //Quemados en el código!! se definen en Ventana::pintarCuadricula()

    colorFichaSeleccionada=QColor(0,180,180,255);

    //Inicializo la matriz de cuadros
    matrizCuadrados = new QGraphicsRectItem**[6];
    for (int i = 0; i < 6; ++i)
        matrizCuadrados[i] = new QGraphicsRectItem*[6];

    //Timer para las animaciones
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animar()));
    tiempo=0;
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
            imagenesFichasBlancas[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/H.png"),this);
            imagenesFichasNegras[i]=new Ficha(QSizeF(540,540),QPixmap("Imagenes/h.png"),this);
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

        imagenesFichasBlancas[i]->setX(0);
        imagenesFichasBlancas[i]->setY(0);
        imagenesFichasNegras[i]->setX(0);
        imagenesFichasNegras[i]->setY(0);
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

    emit celdaCliqueada(xCelda, yCelda);
}

void Tablero::seleccionarFicha(int xFicha, int yFicha)
{
    QColor colorFicha = matrizCuadrados[yFicha][xFicha]->brush().color();

    if(colorFicha==colorFichaSeleccionada)
    {
        if((xFicha+yFicha)%2==0)
            matrizCuadrados[yFicha][xFicha]->setBrush(QColor(255,255,255,255));
        else
            matrizCuadrados[yFicha][xFicha]->setBrush(QColor(0,0,0,255));
    }
    else
    {
        matrizCuadrados[yFicha][xFicha]->setBrush(colorFichaSeleccionada);
    }

    update(0,0,540,540);
}

void Tablero::seleccionarFicha(int xFicha, int yFicha, int xAnterior, int yAnterior)
{
    matrizCuadrados[yFicha][xFicha]->setBrush(colorFichaSeleccionada);

    if((xAnterior+yAnterior)%2==0)
        matrizCuadrados[yAnterior][xAnterior]->setBrush(QColor(255,255,255,255));
    else
        matrizCuadrados[yAnterior][xAnterior]->setBrush(QColor(0,0,0,255));

    update(0,0,540,540);
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

/*
    Este método es llamado siempore con un movimiento válido
*/
void Tablero::iniciarAnimacion(int ficha_in, bool color_in, int xIni, int yIni, int xFin, int yFin)
{
    int dx = xFin-xIni;
    int dy = yFin-yIni;
    ficha_global=ficha_in;
    color_global=color_in;

    if (ficha_global!=4) //Todas menos el caballo
    {
        if(dx==0 && dy!=0) //Movimiento vertical
        {
            signo = dy>0? 1:-1;
            tiempo=abs(dy);
            tipoMovimiento=0;
        }

        if(dx!=0 && dy==0) //Movimiento horizontal
        {
            signo = dx>0? 1:-1;
            tiempo=abs(dx);
            tipoMovimiento=1;
        }

        if(dx!=0 && dy!=0 && dx==dy) //Movimiento en diagonal
        {
            signo = dy>0? 1:-1;
            tiempo=abs(dx);
            tipoMovimiento=2;
        }
        if(dx!=0 && dy!=0 && dx!=dy) //Movimiento en diagonal
        {
            signo = dy>0? 1:-1;
            tiempo=abs(dx);
            tipoMovimiento=3;
        }
    }
    else //Caballo
    {
        tiempo=3;
        tipoMovimiento=4;

        if(dx==1 && dy==-2) signo = 1;
        if(dx==2 && dy==-1) signo = 2;
        if(dx==2 && dy==1)  signo = 3;
        if(dx==1 && dy==2)  signo = 4;
        if(dx==-1 && dy==2) signo = 5;
        if(dx==-2 && dy==1) signo = 6;
        if(dx==-2 && dy==-1)signo = 7;
        if(dx==-1 && dy==-2)signo = 8;
    }

    timer->start(100);
}

/*
    timpoMovimiento:    0 = vertical
                        1 = horizontal
                        2 = DiagonalPrincipal
                        3 = DiagonalSecundaria
                        4 = Caballo

    signo: es positivo hacia la derecha y abajo. Para las diagonales, crece hacia abajo
*/
void Tablero::animar()
{
    if(tiempo==0)
    {
        timer->stop();
        emit terminoAnimacion();
    }
    else
    {
        tiempo--;
        if(tipoMovimiento==0) moverFicha(ficha_global, color_global, 0, signo);
        if(tipoMovimiento==1) moverFicha(ficha_global, color_global, signo, 0);
        if(tipoMovimiento==2) moverFicha(ficha_global, color_global, signo, signo);
        if(tipoMovimiento==3) moverFicha(ficha_global, color_global, (-1*signo), signo);
        if(tipoMovimiento==4)
        {
            if(signo==1)
            {
                if(tiempo>0) moverFicha(ficha_global, color_global, 0, -1);
                else moverFicha(ficha_global, color_global, 1, 0);
            }
            if(signo==2)
            {
                if(tiempo>0) moverFicha(ficha_global, color_global, 1, 0);
                else moverFicha(ficha_global, color_global, 0, -1);
            }
            if(signo==3)
            {
                if(tiempo>0) moverFicha(ficha_global, color_global, 1, 0);
                else moverFicha(ficha_global, color_global, 0, 1);
            }
            if(signo==4)
            {
                if(tiempo>0) moverFicha(ficha_global, color_global, 0, 1);
                else moverFicha(ficha_global, color_global, 1, 0);
            }
            if(signo==5)
            {
                if(tiempo>0) moverFicha(ficha_global, color_global, 0, 1);
                else moverFicha(ficha_global, color_global, -1, 0);
            }
            if(signo==6)
            {
                if(tiempo>0) moverFicha(ficha_global, color_global, -1, 0);
                else moverFicha(ficha_global, color_global, 0, 1);
            }
            if(signo==7)
            {
                if(tiempo>0) moverFicha(ficha_global, color_global, -1, 0);
                else moverFicha(ficha_global, color_global, 0, -1);
            }
            if(signo==8)
            {
                if(tiempo>0) moverFicha(ficha_global, color_global, 0, -1);
                else moverFicha(ficha_global, color_global, -1, 0);
            }
        }
    }
}

/*
    color:  false=negro, true=blanco
    ficha:  en el orden del arreglo
*/
void Tablero::moverFicha(int ficha, bool color, int dx, int dy)
{
    int posX;
    int posY;

    if(color)
    {
        posX = imagenesFichasBlancas[ficha]->getX() + dx*anchoCelda;
        posY = imagenesFichasBlancas[ficha]->getY() + dy*altoCelda;
        imagenesFichasBlancas[ficha]->animatePosition(QPointF(posX,posY));
        imagenesFichasBlancas[ficha]->setX(posX);
        imagenesFichasBlancas[ficha]->setY(posY);
    }
    else
    {
        posX = imagenesFichasNegras[ficha]->getX() + dx*anchoCelda;
        posY = imagenesFichasNegras[ficha]->getY() + dy*altoCelda;
        imagenesFichasNegras[ficha]->animatePosition(QPointF(posX,posY));
        imagenesFichasNegras[ficha]->setX(posX);
        imagenesFichasNegras[ficha]->setY(posY);
    }
}

void Tablero::eliminarFicha(int ficha, bool color) //Es temporal, toca arreglarlo
{
    if (color)
    {
        this->removeItem(imagenesFichasBlancas[ficha]);
        imagenesFichasBlancas[ficha]->setEnabled(false);
    }
    else
    {
        this->removeItem(imagenesFichasNegras[ficha]);
        imagenesFichasNegras[ficha]->setEnabled(false);
    }
}
