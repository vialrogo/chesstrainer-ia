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
    bool tokenJugador;
    bool finDelJuego;
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
    QTimer* timer;
    QMessageBox* mensajeFinDeJuego;
    bool sePuedeMoverFicha(int ficha, bool color, int xCelda, int yCelda);
    bool empate();

    //Variables para animar despues de eliminar
    int ficha_global_eliminar;
    bool color_global_eliminar;
    int xCelda_eliminar;
    int yCelda_eliminar;

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();
    Ui::Ventana *ui;
    void borrarTablero();
    void crearTablero();
    void crearEstadoDeArreglos(char ** estado_in, int* posBlancasX_in, int* posBlancasY_in, int* posNegrasX_in, int* posNegrasY_in);
    bool colorDeficha(int xCelda, int yCelda);
    int numeroDeFicha(int xCelda, int yCelda);
    void imprimirEstado(char ** estado_in, int* posBlancasX_in, int* posBlancasY_in, int* posNegrasX_in, int* posNegrasY_in);

public slots:
    void acercaDe();
    void newGame();
    void gameEasy();
    void gameMedium();
    void cliquearonEnCelda(int xCelda, int yCelda);
    void cambiarJugador();
    void eliminarFicha();

private slots:
    void game();
};

#endif // VENTANA_H
