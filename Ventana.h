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
    int ficha_global;
    bool color_global;
    int *posBlancasX;
    int *posBlancasY;
    int *posNegrasX;
    int *posNegrasY;
    char** estado;
    Tablero* tablerito;
    MiniMax* minimax;
    void game(int nivel);
    bool movimientoValido(int ficha, bool color, int xCelda, int yCelda);
    bool sePuedeMoverFicha(int ficha, bool color, int xCelda, int yCelda);

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();
    Ui::Ventana *ui;
    void borrarTablero();
    void crearTablero();
    void crearEstadoDeArreglos();
    bool colorDeficha(int xCelda, int yCelda);
    int numeroDeFicha(int xCelda, int yCelda);
    void imprimirEstado();
    void matarFicha(int ficha, bool color);

public slots:
    void acercaDe();
    void newGame();
    void gameEasy(){game(0);};
    void gameMedium(){game(1);};
    void gameHard(){game(2);};
    void cliquearonEnCelda(int xCelda, int yCelda);

};

#endif // VENTANA_H
