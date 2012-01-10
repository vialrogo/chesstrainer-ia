#ifndef TABLERO_H
#define TABLERO_H

#include "Ficha.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <iostream>
#include <QDebug>
#include <QTimer>
#include <QPropertyAnimation>

class Tablero: public QGraphicsScene
{
    Q_OBJECT

public:
    Tablero();
    void crearCuadros(int* posBlancasX, int* posBlancasY, int* posNegrasX, int* posNegrasY);
    void moverFicha(/*char carro, int direccion*/);
//    void iniciarAnimacion(string solucion,bool *direcciones);
    void pararAnimacion();

private:
    Ficha** imagenesFichasBlancas;
    Ficha** imagenesFichasNegras;
    QTimer *timer;

private slots:
    void animar();

signals:
    void terminoAnimacion();
};

#endif // TABLERO_H
