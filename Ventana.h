#ifndef VENTANA_H
#define VENTANA_H

#include <QMainWindow>
#include <QMessageBox>
#include <iostream>
#include <exception>
#include "Tablero.h"
#include "Minimax.h"

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
    int xSelected;
    int ySelected;
    int *posBlancasX;
    int *posBlancasY;
    int *posNegrasX;
    int *posNegrasY;
    char** estado;
    Tablero* tablerito;
    MiniMax* minimax;
    void game(int nivel);

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();
    Ui::Ventana *ui;
    void borrarTablero();
    void crearTablero();
    void crearEstadoDeArreglos();
    void imprimirEstado();

public slots:
    void acercaDe();
    void newGame();
    void gameEasy(){game(0);};
    void gameMedium(){game(1);};
    void gameHard(){game(2);};
    void cliquearonEnCelda(int xCelda, int yCelda);

};

#endif // VENTANA_H
