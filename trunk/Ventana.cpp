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

void Ventana::borrarTablero()
{
    tablerito->clear();
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

void Ventana::crearTablero()
{
    //Inicializo los arreglos (-1 significa que la ficha no ha sido colocada o no existe)
    for (int i = 0; i < 8; ++i) {
        posBlancasX[i]=-1;
        posBlancasY[i]=-1;
        posNegrasX[i]=-1;
        posNegrasY[i]=-1;
    }

    //Creo el vector con todos los puntos existentes en el tablero
    QVector<QPoint> vect;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            vect.append(QPoint(i,j));
        }
    }

    //Inicializo semilla aleatoria
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    int tmp;
    QPoint ptmp;

    //Coloco Rey Blanco
    tmp=qrand()%36;
    ptmp=vect.at(tmp);
    posBlancasX[7]=ptmp.rx();
    posBlancasY[7]=ptmp.ry();
    vect.remove(tmp);
    crearEstadoDeArreglos();

    //Coloco Rey Negro
    while(true)
    {
        tmp=qrand()%35;
        ptmp=vect.at(tmp);
        posNegrasX[7]= ptmp.rx();
        posNegrasY[7]= ptmp.ry();
        vect.remove(tmp);
        crearEstadoDeArreglos();

        if(verificarJaque(true))
            vect.append(ptmp);
        else
            break;
    }

    //Coloco resto fichas blancas
    int i=0;
    while(true)
    {
        if(i==7) break;

        tmp=qrand()%(34-i);
        ptmp=vect.at(tmp);
        posBlancasX[i]= ptmp.rx();
        posBlancasY[i]= ptmp.ry();
        vect.remove(tmp);
        crearEstadoDeArreglos();

        if(verificarJaque(false))
            vect.append(ptmp);
        else
            i++;
    }

    //Coloco resto fichas negras
    i=0;
    while(true)
    {
        if(i==7) break;

        tmp=qrand()%(27-i);
        ptmp=vect.at(tmp);
        posNegrasX[i]= ptmp.rx();
        posNegrasY[i]= ptmp.ry();
        vect.remove(tmp);
        crearEstadoDeArreglos();

        if(verificarJaque(true))
            vect.append(ptmp);
        else
            i++;
    }

    imprimirEstado();

    //Crea el mapa (parte gráfica)
    ui->graphicsView->setHidden(false);
    ui->pushButtonEasy->setHidden(true);
    ui->pushButtonMedium->setHidden(true);
    ui->pushButtonHard->setHidden(true);

    borrarTablero();
    tablerito->pintarCuadricula();
    tablerito->crearFichas(posBlancasX,posBlancasY,posNegrasX,posNegrasY);
    tablerito->setEstado(estado);
}

bool Ventana::verificarJaque(bool color) //color=false => negras / color=true => blancas
{
    /*
        B = 66    b = 98
        C = 67    c = 99
        K = 75    k = 107
        P = 80    p = 112
        Q = 81    q = 113
     */

    int delta = color? 32 : 0;

    int reyX = color? posBlancasX[7] : posNegrasX[7];
    int reyY = color? posBlancasY[7] : posNegrasY[7];

    int dxDiago[] = {-1, 1,-1, 1};
    int dyDiago[] = {-1,-1, 1, 1};

    int dxRectas[] = { 0, 1, 0,-1};
    int dyRectas[] = {-1, 0, 1, 0};

    int dxCaballo[] = {-2,-2,-1,-1, 1, 1, 2, 2};
    int dyCaballo[] = {-1, 1,-2, 2,-2, 2,-1, 1};

    int dxRey[] = {-1,-1,-1, 0, 0, 1, 1, 1};
    int dyRey[] = {-1, 0, 1,-1, 1,-1, 0, 1};

    int idx=0;
    int count=1;
    int xx = 0;
    int yy = 0;
    bool respuesta = false;

    //alfiles-reinaDiagonal
    idx=0;
    count=1;
    while (true)
    {
        if(idx > 3) break;

        xx = reyX+(count*dxDiago[idx]);
        yy = reyY+(count*dyDiago[idx]);

        if(xx<0 || xx>5 || yy<0 || yy>5)
        {
            count=1;
            idx++;
        }
        else
        {
            if(estado[yy][xx] == ' ')
                count++;
            else{
                if(estado[yy][xx] == (81+delta) || estado[yy][xx] == (66+delta))
                    return true;
                else
                {
                    count=1;
                    idx++;
                }
            }
        }
    }

    //ReinaColumna
    idx=0;
    count=1;
    while (true)
    {
        if(idx > 3) break;

        xx = reyX+(count*dxRectas[idx]);
        yy = reyY+(count*dyRectas[idx]);

        if(xx<0 || xx>5 || yy<0 || yy>5)
        {
            count=1;
            idx++;
        }
        else
        {
            if(estado[yy][xx] == ' ')
                count++;
            else{
                if(estado[yy][xx] == (81+delta))
                    return true;
                else
                {
                    count=1;
                    idx++;
                }
            }
        }
    }

    //Caballos
    for (int i = 0; i < 8; ++i)
    {
        xx = reyX + dxCaballo[i];
        yy = reyY + dyCaballo[i];

        if(xx<0 || xx>5 || yy<0 || yy>5)
            continue;
        else
            if(estado[yy][xx] == (67+delta))
                return true;
    }

    //Peones
    if(color)
    {
        if(reyX>0 && reyY>0)
            if(estado[reyY-1][reyX-1] == 112)
                return true;

        if(reyX<5 && reyY>0)
            if(estado[reyY-1][reyX+1] == 112)
                return true;
    }
    else
    {
        if(reyX>0 && reyY<5)
            if(estado[reyY+1][reyX-1] == 80)
                return true;

        if(reyX<5 && reyY<5)
            if(estado[reyY+1][reyX+1] == 80)
                return true;
    }

    //Otro rey
    for (int i = 0; i < 8; ++i)
    {
        xx = reyX + dxRey[i];
        yy = reyY + dyRey[i];

        if(xx<0 || xx>5 || yy<0 || yy>5)
            continue;
        else
            if(estado[yy][xx] == (75+delta))
                return true;
    }

    return respuesta;
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
        if(posBlancasY[i]!=-1 && posBlancasX[i]!=-1)
        {
            if(i<4) estado[posBlancasY[i]][posBlancasX[i]]='P';
            if(i==4) estado[posBlancasY[i]][posBlancasX[i]]='C';
            if(i==5) estado[posBlancasY[i]][posBlancasX[i]]='B';
            if(i==6) estado[posBlancasY[i]][posBlancasX[i]]='Q';
            if(i==7) estado[posBlancasY[i]][posBlancasX[i]]='K';
        }
        if(posNegrasY[i]!=-1 && posNegrasX[i]!=-1)
        {
            if(i<4) estado[posNegrasY[i]][posNegrasX[i]]='p';
            if(i==4) estado[posNegrasY[i]][posNegrasX[i]]='c';
            if(i==5) estado[posNegrasY[i]][posNegrasX[i]]='b';
            if(i==6) estado[posNegrasY[i]][posNegrasX[i]]='q';
            if(i==7) estado[posNegrasY[i]][posNegrasX[i]]='k';
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
    borrarTablero();
    ui->graphicsView->setHidden(true);
    ui->pushButtonEasy->setHidden(false);
    ui->pushButtonMedium->setHidden(false);
    ui->pushButtonHard->setHidden(false);
}

void Ventana::gameEasy()
{
    crearTablero();
    cout<<"Empieza un juego fácil"<<endl;
}

void Ventana::gameMedium()
{
    crearTablero();
    cout<<"Empieza un juego intermedio"<<endl;
}

void Ventana::gameHard()
{
    crearTablero();
    cout<<"Empieza un juego difícil"<<endl;
}

