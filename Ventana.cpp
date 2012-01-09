#include "Ventana.h"
#include "ui_Ventana.h"

Ventana::Ventana(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);
    this->setWindowTitle("Project ChessTrainer-IA");

    //Dimenciones de la escena --> FALTA AJUSTAR!!!
    W=420; //70
    H=420; //70

    //Se agrega el Tablero a la GUI
    tablerito = new Tablero();
    tablerito->setSceneRect(0,0,W,H);
    ui->graphicsView->setScene(tablerito);

    //Inicialización
    pintarCuadricula();

    connect(ui->actionQuit, SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(acercaDe()));
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::borrarMapa()
{
    tablerito->clear();
}

void Ventana::pintarCuadricula()
{
    borrarMapa();

    int filas=6;
    int columnas=6;

    int ancho = W/filas;
    int alto = H/columnas;

    for (int i = 0; i <=filas; ++i)
    {
        QGraphicsLineItem *line = new QGraphicsLineItem(i*ancho,0,i*ancho,columnas*alto);
        line->setPen(QColor(180,180,180,255));//Coloca el color de la cuadricula: R,G,B,alfa
        tablerito->addItem(line);
    }

    for (int i = 0; i <= columnas; ++i)
    {
        QGraphicsLineItem *line = new QGraphicsLineItem(0,i*alto,filas*ancho,i*alto);
        line->setPen(QColor(180,180,180,255));//Coloca el color de la cuadricula: R,G,B,alfa
        tablerito->addItem(line);
    }
}

void Ventana::acercaDe()
{
    QMessageBox msgBox;
    msgBox.setTextFormat(Qt::RichText);
    msgBox.setWindowTitle("About");
    msgBox.setText("<h3>Project ChessTrainer-IA</h3>");
    msgBox.setInformativeText("Create by: \n    Victor Alberto Romero\n    Erika Suarez Valencia");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
    return;
}
