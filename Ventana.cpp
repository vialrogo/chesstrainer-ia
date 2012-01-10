#include "Ventana.h"
#include "ui_Ventana.h"

Ventana::Ventana(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);
    this->setWindowTitle("Project ChessTrainer-IA");

    //Dimenciones de la escena --> FALTA AJUSTAR!!!
    W=540; //80x6 de ancho por celda + 30x2 de los bordes
    H=540; //80x6 de largo por celda + 30x2 de los bordes

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

    int deltaX=30+1; //Empirico, tiene que ver con que no aparezcan los scroll
    int deltaY=30+1; //Empirico, tiene que ver con que no aparezcan los scroll
    int ancho = 80;
    int alto = 80;

    //Cuadros
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            QGraphicsRectItem *cuadrado = new QGraphicsRectItem(i*alto+deltaY,j*ancho+deltaX,ancho,alto,0,tablerito);
            cuadrado->setPen(QColor(180,180,180,255));//Color de linea

            if((i+j)%2==0)
                cuadrado->setBrush(QColor(255,255,255,255));//Cuadros Blancos
            else
                cuadrado->setBrush(QColor(0,0,0,255));//Cuadros Negros
        }
    }

    //Texto
    QString letras[6] = {"a","b","c","d","e","f"};
    QString numeros[6] = {"1","2","3","4","5","6"};
    QFont fuente("Times", 12, QFont::Monospace);
    int dxnumeros=5;
    int dyletras=4;

    for (int i = 0; i < 6; ++i)
    {
        QGraphicsTextItem* letraSuperior = new QGraphicsTextItem(letras[i],0,tablerito);
        letraSuperior->setFont(fuente);
        letraSuperior->setPos(deltaX+40+(i*80),dyletras);
        QGraphicsTextItem* letraInferior = new QGraphicsTextItem(letras[i],0,tablerito);
        letraInferior->setFont(fuente);
        letraInferior->setPos(deltaX+40+(i*80),deltaY+480+dyletras);
        QGraphicsTextItem* numeroSuperior = new QGraphicsTextItem(numeros[i],0,tablerito);
        numeroSuperior->setFont(fuente);
        numeroSuperior->setPos(dxnumeros,deltaY+40+(i*80));
        QGraphicsTextItem* numeroInferior = new QGraphicsTextItem(numeros[i],0,tablerito);
        numeroInferior->setFont(fuente);
        numeroInferior->setPos(deltaX+480+dxnumeros,deltaY+40+(i*80));
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
