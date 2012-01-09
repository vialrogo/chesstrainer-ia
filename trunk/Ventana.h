#ifndef VENTANA_H
#define VENTANA_H

#include <QMainWindow>
#include <QMessageBox>
#include "Tablero.h"

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

public slots:
    void acercaDe();
};

#endif // VENTANA_H
