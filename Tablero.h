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
    void iniciarAnimacion(int ficha, bool color, int xIni, int yIni, int xFin, int yFin);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void seleccionarFicha(int xFicha, int yFicha);
    void seleccionarFicha(int xFicha, int yFicha, int xAnterior, int yAnterior);
    void eliminarFicha(int ficha, bool color);

private:
    //Variables Animación
    int tiempo;
    int ficha_global;
    bool color_global;
    int tipoMovimiento;
    int signo;

    //Variables Tablero
    int deltaX;
    int deltaY;
    int anchoCelda;
    int altoCelda;
    QColor colorFichaSeleccionada;
    QGraphicsRectItem *** matrizCuadrados;
    Ficha** imagenesFichasBlancas;
    Ficha** imagenesFichasNegras;
    Ficha** imagenesFichasBlancasMinisGrises;
    Ficha** imagenesFichasNegrasMinisGrises;
    Ficha** imagenesFichasBlancasMinisNormal;
    Ficha** imagenesFichasNegrasMinisNormal;
    QTimer *timer;
    void moverFicha(int ficha, bool color, int dx, int dy);

private slots:
    void animar();

signals:
    void terminoAnimacion();
    void celdaCliqueada(int X, int Y);
};

#endif // TABLERO_H
