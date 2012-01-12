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

using namespace std;

class Tablero: public QGraphicsScene
{
    Q_OBJECT

public:
    Tablero();
    void crearFichas(int* posBlancasX, int* posBlancasY, int* posNegrasX, int* posNegrasY);
    void pintarCuadricula();
    void moverFicha(/*char carro, int direccion*/);
//    void iniciarAnimacion(string solucion,bool *direcciones);
    void pararAnimacion();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void setEstado(char** estado_in);

private:
    int deltaX;
    int deltaY;
    int anchoCelda;
    int altoCelda;
    char** estado;
    int xSelected;
    int ySelected;
    QGraphicsRectItem *** matrizCuadrados;
    Ficha** imagenesFichasBlancas;
    Ficha** imagenesFichasNegras;
    QTimer *timer;

private slots:
    void animar();

signals:
    void terminoAnimacion();
};

#endif // TABLERO_H
