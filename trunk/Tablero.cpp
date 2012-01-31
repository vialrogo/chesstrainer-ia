#include "Tablero.h"

Tablero::Tablero()
{
    //Variables globales
    deltaX=21; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    deltaY=81; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    anchoCelda = 80; //Quemados en el código!! se definen en Ventana::pintarCuadricula()
    altoCelda = 80; //Quemados en el código!! se definen en Ventana::pintarCuadricula()

    //Color cuando se selecciona una ficha
    colorFichaSeleccionada=QColor(0,180,180,255);

    //tiempo de la animación
    tiempoAnimacion=200;
    tiempo=0;

    //Inicializo la matriz de cuadros
    matrizCuadrados = new QGraphicsRectItem**[6];
    for (int i = 0; i < 6; ++i)
        matrizCuadrados[i] = new QGraphicsRectItem*[6];

    //Timer para las animaciones
    timer = new QTimer(this);
    timerEliminar = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(animar()));
    connect(timerEliminar, SIGNAL(timeout()), this, SLOT(eliminarImagenFicha()));
}

void Tablero::crearFichas(int *posBlancasX, int *posBlancasY, int *posNegrasX, int *posNegrasY)
{
    imagenesFichasBlancas = new  Ficha*[8];
    imagenesFichasNegras = new  Ficha*[8];
    imagenesFichasBlancasMinisGrises = new  Ficha*[8];
    imagenesFichasNegrasMinisGrises = new  Ficha*[8];
    imagenesFichasBlancasMinisNormal = new  Ficha*[8];
    imagenesFichasNegrasMinisNormal = new  Ficha*[8];

    for (int i = 0; i < 8; ++i)
    {
        if(i<4) //Peones
        {
            imagenesFichasBlancas[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/P.png"),this);
            imagenesFichasNegras[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/p.png"),this);
            imagenesFichasBlancasMinisGrises[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/mP.png"),this);
            imagenesFichasNegrasMinisGrises[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/mP.png"),this);
            imagenesFichasBlancasMinisNormal[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/MP.png"),this);
            imagenesFichasNegrasMinisNormal[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/Mp.png"),this);
        }

        if(i==4) //Caballo
        {
            imagenesFichasBlancas[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/H.png"),this);
            imagenesFichasNegras[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/h.png"),this);
            imagenesFichasBlancasMinisGrises[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/mH.png"),this);
            imagenesFichasNegrasMinisGrises[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/mH.png"),this);
            imagenesFichasBlancasMinisNormal[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/MH.png"),this);
            imagenesFichasNegrasMinisNormal[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/Mh.png"),this);
        }

        if(i==5) //Alfil
        {
            imagenesFichasBlancas[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/B.png"),this);
            imagenesFichasNegras[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/b.png"),this);
            imagenesFichasBlancasMinisGrises[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/mB.png"),this);
            imagenesFichasNegrasMinisGrises[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/mB.png"),this);
            imagenesFichasBlancasMinisNormal[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/MB.png"),this);
            imagenesFichasNegrasMinisNormal[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/Mb.png"),this);
        }

        if(i==6) //Reina
        {
            imagenesFichasBlancas[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/Q.png"),this);
            imagenesFichasNegras[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/q.png"),this);
            imagenesFichasBlancasMinisGrises[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/mQ.png"),this);
            imagenesFichasNegrasMinisGrises[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/mQ.png"),this);
            imagenesFichasBlancasMinisNormal[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/MQ.png"),this);
            imagenesFichasNegrasMinisNormal[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/Mq.png"),this);
        }

        if(i==7) //Rey
        {
            imagenesFichasBlancas[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/K.png"),this);
            imagenesFichasNegras[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/k.png"),this);
            imagenesFichasBlancasMinisGrises[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/mK.png"),this);
            imagenesFichasNegrasMinisGrises[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/mK.png"),this);
            imagenesFichasBlancasMinisNormal[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/MK.png"),this);
            imagenesFichasNegrasMinisNormal[i]=new Ficha(QSizeF(520,640),QPixmap("Imagenes/Mk.png"),this);
        }

        //Fichas de juego
        imagenesFichasBlancas[i]->setOffset(posBlancasX[i]*anchoCelda+deltaX,posBlancasY[i]*altoCelda+deltaY);
        this->addItem(imagenesFichasBlancas[i]);
        imagenesFichasNegras[i]->setOffset(posNegrasX[i]*anchoCelda+deltaX,posNegrasY[i]*altoCelda+deltaY);
        this->addItem(imagenesFichasNegras[i]);

        int xArriba = deltaX+i*40;
        int yArriba = 18;
        int xAbajo = deltaX+160+i*40;
        int yAbajo = deltaY+480+20+5;

        //Miniaturas grises
        imagenesFichasBlancasMinisNormal[i]->setOffset(xArriba,yArriba);
        imagenesFichasBlancasMinisGrises[i]->setOffset(xArriba,yArriba);
        this->addItem(imagenesFichasBlancasMinisGrises[i]);
        imagenesFichasNegrasMinisNormal[i]->setOffset(xAbajo,yAbajo);
        imagenesFichasNegrasMinisGrises[i]->setOffset(xAbajo,yAbajo);
        this->addItem(imagenesFichasNegrasMinisGrises[i]);

        //Fichas
        imagenesFichasBlancas[i]->setX(0);
        imagenesFichasBlancas[i]->setY(0);
        imagenesFichasNegras[i]->setX(0);
        imagenesFichasNegras[i]->setY(0);

        //Miniatura Gris
        imagenesFichasBlancasMinisGrises[i]->setX(xArriba-20);
        imagenesFichasBlancasMinisGrises[i]->setY(yArriba-20);
        imagenesFichasNegrasMinisGrises[i]->setX(xAbajo-20);
        imagenesFichasNegrasMinisGrises[i]->setY(yAbajo-20);

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

    update(0,0,520,640);
}

void Tablero::seleccionarFicha(int xFicha, int yFicha, int xAnterior, int yAnterior)
{
    matrizCuadrados[yFicha][xFicha]->setBrush(colorFichaSeleccionada);

    if((xAnterior+yAnterior)%2==0)
        matrizCuadrados[yAnterior][xAnterior]->setBrush(QColor(255,255,255,255));
    else
        matrizCuadrados[yAnterior][xAnterior]->setBrush(QColor(0,0,0,255));

    update(0,0,520,640);
}

void Tablero::pintarCuadricula()
{
    clear();

    //Cuadros
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            matrizCuadrados[j][i] = new QGraphicsRectItem(i*altoCelda+deltaX,j*anchoCelda+deltaY,anchoCelda,altoCelda,0,this);
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
    QFont fuente("Times", 11, QFont::Monospace);
    int dxnumeros=5;
    int dyletras=0;

    for (int i = 0; i < 6; ++i)
    {
        QGraphicsTextItem* letraSuperior = new QGraphicsTextItem(letras[i],0,this);
        letraSuperior->setFont(fuente);
        letraSuperior->setPos(deltaX+40+(i*80),dyletras+60);
        QGraphicsTextItem* letraInferior = new QGraphicsTextItem(letras[i],0,this);
        letraInferior->setFont(fuente);
        letraInferior->setPos(deltaX+40+(i*80),deltaY+480+dyletras-1);
        QGraphicsTextItem* numeroSuperior = new QGraphicsTextItem(numeros[i],0,this);
        numeroSuperior->setFont(fuente);
        numeroSuperior->setPos(dxnumeros,deltaY+40+(i*80));
        QGraphicsTextItem* numeroInferior = new QGraphicsTextItem(numeros[i],0,this);
        numeroInferior->setFont(fuente);
        numeroInferior->setPos(deltaX+480+dxnumeros-3,deltaY+40+(i*80));
    }
}

/*
    Este método es llamado siempore con un movimiento válido
*/
void Tablero::iniciarAnimacion(int ficha_in, bool color_in, int xIni, int yIni, int xFin, int yFin, bool tocaElimiarLuego)
{
    tocaEliminarLuego_global=tocaElimiarLuego;
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

    timer->start(tiempoAnimacion);
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

        if(tocaEliminarLuego_global) emit empezarEliminar();
        else emit terminoAnimacion();
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
        imagenesFichasBlancas[ficha]->animatePosition(QPointF(posX,posY),tiempoAnimacion);
        imagenesFichasBlancas[ficha]->setX(posX);
        imagenesFichasBlancas[ficha]->setY(posY);
    }
    else
    {
        posX = imagenesFichasNegras[ficha]->getX() + dx*anchoCelda;
        posY = imagenesFichasNegras[ficha]->getY() + dy*altoCelda;
        imagenesFichasNegras[ficha]->animatePosition(QPointF(posX,posY),tiempoAnimacion);
        imagenesFichasNegras[ficha]->setX(posX);
        imagenesFichasNegras[ficha]->setY(posY);
    }
}

void Tablero::eliminarFicha(int ficha, bool color, int X, int Y) //Es temporal, toca arreglarlo
{
    int dx;
    int dy;
    int posX;
    int posY;
    int saltoTiempoAnimacion=100;
    int tiempoAnimacionEliminar;

    ficha_global_eliminar=ficha;
    color_global_eliminar=color;

    if (color)
    {
        //Animo la ficha que se va
        dx= (X*anchoCelda + deltaX)-imagenesFichasBlancasMinisGrises[ficha]->getX();
        dy= (Y*altoCelda + deltaY)-imagenesFichasBlancasMinisGrises[ficha]->getY();
        posX = imagenesFichasBlancas[ficha]->getX() - dx;
        posY = imagenesFichasBlancas[ficha]->getY() - dy;
        tiempoAnimacionEliminar= (sqrt(pow(dx,2)+pow(dy,2))/80)*saltoTiempoAnimacion;
        imagenesFichasBlancas[ficha]->animatePosition(QPointF(posX,posY),tiempoAnimacionEliminar);
    }
    else
    {
        //Animo la ficha que se va
        dx= (X*anchoCelda + deltaX)-imagenesFichasNegrasMinisGrises[ficha]->getX();
        dy= (Y*altoCelda + deltaY)-imagenesFichasNegrasMinisGrises[ficha]->getY();
        posX = imagenesFichasNegras[ficha]->getX() - dx;
        posY = imagenesFichasNegras[ficha]->getY() - dy;
        tiempoAnimacionEliminar= (sqrt(pow(dx,2)+pow(dy,2))/80)*saltoTiempoAnimacion;
        imagenesFichasNegras[ficha]->animatePosition(QPointF(posX,posY),tiempoAnimacionEliminar);
    }

    timerEliminar->start(tiempoAnimacionEliminar);
}

void Tablero::eliminarImagenFicha()
{
    timerEliminar->stop();

    if(color_global_eliminar)
    {
        //Quito la ficha
        this->removeItem(imagenesFichasBlancas[ficha_global_eliminar]);
        imagenesFichasBlancas[ficha_global_eliminar]->setEnabled(false);

        //Cambio la mini ficha
        this->removeItem(imagenesFichasBlancasMinisGrises[ficha_global_eliminar]);
        imagenesFichasBlancasMinisGrises[ficha_global_eliminar]->setEnabled(false);
        this->addItem(imagenesFichasBlancasMinisNormal[ficha_global_eliminar]);
    }
    else
    {
        //Quito la ficha
        this->removeItem(imagenesFichasNegras[ficha_global_eliminar]);
        imagenesFichasNegras[ficha_global_eliminar]->setEnabled(false);

        //Cambio la mini ficha
        this->removeItem(imagenesFichasNegrasMinisGrises[ficha_global_eliminar]);
        imagenesFichasNegrasMinisGrises[ficha_global_eliminar]->setEnabled(false);
        this->addItem(imagenesFichasNegrasMinisNormal[ficha_global_eliminar]);
    }

    emit terminoAnimacion();
}
