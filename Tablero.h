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
#include <QPoint>
#include <QPropertyAnimation>

using namespace std;

class Tablero: public QGraphicsScene
{
    Q_OBJECT

public:
    Tablero();
    void crearFichas(int* posBlancasX, int* posBlancasY, int* posNegrasX, int* posNegrasY);
    void pintarCuadricula();
    void moverFicha(int ficha, bool color, int xIni, int yIni, int xFin, int yFin);
//    void iniciarAnimacion(string solucion,bool *direcciones);
    void pararAnimacion();
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void setEstado(char** estado_in);
    void seleccionarFicha(int xFicha, int yFicha);
    void seleccionarFicha(int xFicha, int yFicha, int xAnterior, int yAnterior);

private:
    int deltaX;
    int deltaY;
    int anchoCelda;
    int altoCelda;
    char** estado;
    QColor colorFichaSeleccionada;
    QGraphicsRectItem *** matrizCuadrados;
    Ficha** imagenesFichasBlancas;
    Ficha** imagenesFichasNegras;
    QTimer *timer;

private slots:
    void animar();

signals:
    void terminoAnimacion();
    void celdaCliqueada(int X, int Y);
};

#endif // TABLERO_H
