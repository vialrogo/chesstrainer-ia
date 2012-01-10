#ifndef VENTANA_H
#define VENTANA_H

#include <QMainWindow>
#include <QMessageBox>
#include <iostream>
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
    Tablero* tablerito;

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();
    Ui::Ventana *ui;
    void borrarMapa();
    void pintarCuadricula();
    void crearMapa();

public slots:
    void acercaDe();
    void newGame();
    void gameEasy();
    void gameMedium();
    void gameHard();
};

#endif // VENTANA_H
