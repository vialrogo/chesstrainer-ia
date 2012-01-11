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

    //Arreglos con las posiciones de las fichas
    posBlancasX = new int[8];
    posBlancasY = new int[8];
    posNegrasX = new int[8];
    posNegrasY = new int[8];

    //Estado del tablero
    estado = new char*[6];
    for (int i = 0; i < 6; ++i)
        estado[i] = new char[6];

    //Se agrega el Tablero a la GUI
    tablerito = new Tablero();
    tablerito->setSceneRect(0,0,W,H);
    ui->graphicsView->setScene(tablerito);
    ui->graphicsView->setHidden(true);

    connect(ui->actionQuit, SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(acercaDe()));
    connect(ui->actionNew_Game,SIGNAL(triggered()),this,SLOT(newGame()));
    connect(ui->pushButtonEasy,SIGNAL(clicked()),this,SLOT(gameEasy()));
    connect(ui->pushButtonMedium,SIGNAL(clicked()),this,SLOT(gameMedium()));
    connect(ui->pushButtonHard,SIGNAL(clicked()),this,SLOT(gameHard()));
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

void Ventana::crearMapa()
{
    //Para colocar las fichas en posición aleatoria. Se puede mejorar
    QVector<QPoint> vect;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            vect.append(QPoint(i,j));
        }
    }

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int tmp;
    QPoint ptmp;

    for (int i = 0; i < 8; ++i) {
        tmp=qrand()%(36-(i*2));
        ptmp=vect.at(tmp);
        posBlancasX[i]=ptmp.rx();
        posBlancasY[i]=ptmp.ry();
        vect.remove(tmp);

        tmp=qrand()%(35-(i*2));
        ptmp=vect.at(tmp);
        posNegrasX[i]= ptmp.rx();
        posNegrasY[i]= ptmp.ry();
        vect.remove(tmp);
    }

    crearEstadoDeArreglos();
    imprimirEstado();

    //Verifica y arregla jaque
    /** Pendiente!!!*/

    //Crea el mapa (parte gráfica)
    borrarMapa();
    pintarCuadricula();

    ui->graphicsView->setHidden(false);
    ui->pushButtonEasy->setHidden(true);
    ui->pushButtonMedium->setHidden(true);
    ui->pushButtonHard->setHidden(true);

    tablerito->crearCuadros(posBlancasX,posBlancasY,posNegrasX,posNegrasY);
}

void Ventana::crearEstadoDeArreglos()
{
    //Vacio la matriz
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            estado[i][j]=' ';
        }
    }

    for (int i = 0; i < 8; ++i)
    {
        if(i<4){
            estado[posBlancasY[i]][posBlancasX[i]]='P';
            estado[posNegrasY[i]][posNegrasX[i]]='p';
        }
        if(i==4){
            estado[posBlancasY[i]][posBlancasX[i]]='C';
            estado[posNegrasY[i]][posNegrasX[i]]='c';
        }
        if(i==5){
            estado[posBlancasY[i]][posBlancasX[i]]='B';
            estado[posNegrasY[i]][posNegrasX[i]]='b';
        }
        if(i==6){
            estado[posBlancasY[i]][posBlancasX[i]]='Q';
            estado[posNegrasY[i]][posNegrasX[i]]='q';
        }
        if(i==7){
            estado[posBlancasY[i]][posBlancasX[i]]='K';
            estado[posNegrasY[i]][posNegrasX[i]]='k';
        }
    }
}

void Ventana::imprimirEstado()
{
    for (int i = 0; i < 6; ++i) {
        cout<<"+---+---+---+---+---+---+"<<endl;
        for (int j = 0; j < 6; ++j) {
            cout<<"| "<<estado[i][j]<<" ";
        }
        cout<<"|"<<endl;
    }
    cout<<"+---+---+---+---+---+---+"<<endl<<endl;
}

void Ventana::newGame()
{
    //Se vuelve a la pantalla con botones
    borrarMapa();
    ui->graphicsView->setHidden(true);
    ui->pushButtonEasy->setHidden(false);
    ui->pushButtonMedium->setHidden(false);
    ui->pushButtonHard->setHidden(false);
}

void Ventana::gameEasy()
{
    crearMapa();
    cout<<"Empieza un juego fácil"<<endl;
}

void Ventana::gameMedium()
{
    crearMapa();
    cout<<"Empieza un juego intermedio"<<endl;
}

void Ventana::gameHard()
{
    crearMapa();
    cout<<"Empieza un juego difícil"<<endl;
}

