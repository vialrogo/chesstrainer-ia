#ifndef VENTANA_H
#define VENTANA_H

#include <QMainWindow>
#include <QMessageBox>
#include <iostream>
#include <exception>
#include "Tablero.h"

using namespace std;

namespace Ui {
class Ventana;
}

class Ventana : public QMainWindow
{
    Q_OBJECT

private:
    int W;
    int H;
    int *posBlancasX;
    int *posBlancasY;
    int *posNegrasX;
    int *posNegrasY;
    char** estado;
    Tablero* tablerito;

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();
    Ui::Ventana *ui;
    void borrarTablero();

    void crearTablero();
    void crearEstadoDeArreglos();
    void imprimirEstado();
    bool verificarJaque(bool color); //Es posible que este método no vaya en esta clase

public slots:
    void acercaDe();
    void newGame();
    void gameEasy();
    void gameMedium();
    void gameHard();
};

#endif // VENTANA_H
