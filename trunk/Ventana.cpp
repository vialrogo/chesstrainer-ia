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

    //Celda seleccionada
    xSelected=-1;
    ySelected=-1;
    ficha_global=-1;
    color_global=NULL;

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
    connect(tablerito,SIGNAL(celdaCliqueada(int,int)),this,SLOT(cliquearonEnCelda(int,int)));
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
    minimax->definirVariables(estado,posBlancasX,posBlancasY,posNegrasX,posNegrasY);

    //Coloco Rey Negro
    while(true)
    {
        tmp=qrand()%35;
        ptmp=vect.at(tmp);
        posNegrasX[7]= ptmp.rx();
        posNegrasY[7]= ptmp.ry();
        vect.remove(tmp);
        crearEstadoDeArreglos();
        minimax->definirVariables(estado,posBlancasX,posBlancasY,posNegrasX,posNegrasY);

        if(minimax->verificarJaque(true))
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
        minimax->definirVariables(estado,posBlancasX,posBlancasY,posNegrasX,posNegrasY);

        if(minimax->verificarJaque(false))
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
        minimax->definirVariables(estado,posBlancasX,posBlancasY,posNegrasX,posNegrasY);

        if(minimax->verificarJaque(true))
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
    //Para imprimir la matriz
    for (int i = 0; i < 6; ++i) {
        cout<<"+---+---+---+---+---+---+"<<endl;
        for (int j = 0; j < 6; ++j) {
            cout<<"| "<<estado[i][j]<<" ";
        }
        cout<<"|"<<endl;
    }
    cout<<"+---+---+---+---+---+---+"<<endl<<endl;

    //Para imprimir los arreglos
    cout<<"+-------+---+---+---+---+---+---+---+---+"<<endl;
    cout<<"| Color | P | P | P | P | H | B | Q | K |"<<endl;
    cout<<"+-------+---+---+---+---+---+---+---+---+"<<endl;
    cout<<"|Blanco |";
    for (int i = 0; i < 8; ++i) cout<<posBlancasX[i]<<","<<posBlancasY[i]<<"|";
    cout<<endl;
    cout<<"+-------+---+---+---+---+---+---+---+---+"<<endl;
    cout<<"|Negro  |";
    for (int i = 0; i < 8; ++i) cout<<posNegrasX[i]<<","<<posNegrasY[i]<<"|";
    cout<<endl;
    cout<<"+-------+---+---+---+---+---+---+---+---+"<<endl<<endl;
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

void Ventana::game(int nivel) // Facil=0, Medio=1, Dificil=2
{
    minimax = new MiniMax(nivel);
    crearTablero();

    if(nivel==0)
        cout<<"Empieza un juego fácil"<<endl;

    if(nivel==1)
        cout<<"Empieza un juego intermedio"<<endl;

    if(nivel==2)
        cout<<"Empieza un juego elda, yCelda);difícil"<<endl;
}

/*
    Devuelve el color de la ficha que se encuentra en la posición [y,x]
  */
bool Ventana::colorDeficha(int xCelda, int yCelda)
{
    if(estado[yCelda][xCelda]<82) return true;
    else return false;
}

/*
    Devuelve el numero de la ficha (en el arreglo de posiciones, por lo que diferencia cada peon por ejemplo
    de la ficha que se encuentra en la posición [y,x]
  */
int Ventana::numeroDeFicha(int xCelda, int yCelda)
{
    for (int i = 0; i < 8; ++i) {
        if ((posBlancasX[i]==xCelda && posBlancasY[i]==yCelda) || (posNegrasX[i]==xCelda && posNegrasY[i]==yCelda))
            return i;
    }
    return -1;
}

void Ventana::cliquearonEnCelda(int xCelda, int yCelda)
{
    int ficha_tmp;
    bool color_tmp;

    if(estado[yCelda][xCelda]!=' ') //Se cliqueo en una ficha
    {
        ficha_global = numeroDeFicha(xCelda,yCelda);
        color_global = colorDeficha(xCelda,yCelda);

        if(xSelected==-1 && ySelected==-1) //No hay ninguna ficha seleccionada
        {
            tablerito->seleccionarFicha(xCelda,yCelda);
            xSelected=xCelda;
            ySelected=yCelda;
        }
        else
        {
            if(xSelected==xCelda && ySelected==yCelda) //Se volvió a cliclear en la ficha seleccionada
            {
                tablerito->seleccionarFicha(xCelda,yCelda);
                xSelected=-1;
                ySelected=-1;
            }
            else //Se cliqueo en una ficha, cuando ya había OTRA seleccionada
            {
                ficha_tmp=numeroDeFicha(xSelected,ySelected);
                color_tmp=colorDeficha(xSelected,ySelected);

                if(movimientoValido(ficha_tmp,color_tmp,xCelda,yCelda)) //Se cliqueó en una ficha del color contrario (o la come, o es inválido)
                {
                    tablerito->seleccionarFicha(xSelected,ySelected);
                    matarFicha(ficha_global,color_global);
                    tablerito->iniciarAnimacion(ficha_tmp, color_tmp, xSelected, ySelected, xCelda, yCelda);
                    xSelected=-1;
                    ySelected=-1;

                    if(color_tmp) {
                        posBlancasX[ficha_tmp]=xCelda;
                        posBlancasY[ficha_tmp]=yCelda;
                    }else {
                        posNegrasX[ficha_tmp]=xCelda;
                        posNegrasY[ficha_tmp]=yCelda;
                    }

                    crearEstadoDeArreglos();
                }
                else // Se cliqueó en una ficha del mismo color (cambio de ficha seleccionada)
                {
                    tablerito->seleccionarFicha(xCelda,yCelda,xSelected,ySelected);
                    xSelected=xCelda;
                    ySelected=yCelda;
                }
            }

        }
    }
    else //Se cliqueo en un espacio en blanco
    {
        if(xSelected!=-1 && ySelected!=-1) //Ya había una ficha seleccionada
        {
            if(movimientoValido(numeroDeFicha(xSelected,ySelected),colorDeficha(xSelected,ySelected),xCelda,yCelda)) //El movimiento es válido
            {
                tablerito->iniciarAnimacion(ficha_global, color_global, xSelected, ySelected, xCelda, yCelda);

                if(color_global) {
                    posBlancasX[ficha_global]=xCelda;
                    posBlancasY[ficha_global]=yCelda;
                }else {
                    posNegrasX[ficha_global]=xCelda;
                    posNegrasY[ficha_global]=yCelda;
                }

                crearEstadoDeArreglos();
            }

            tablerito->seleccionarFicha(xSelected,ySelected);
            xSelected=-1;
            ySelected=-1;
        }
    }
}

bool Ventana::sePuedeMoverFicha(int ficha, bool color, int xCelda, int yCelda)
{
    int xOrigen;
    int yOrigen;
    int xx;
    int yy;
    int cont;
    char ctmp;

    if (color) {
        xOrigen = posBlancasX[ficha];
        yOrigen = posBlancasY[ficha];
    } else {
        xOrigen = posNegrasX[ficha];
        yOrigen = posNegrasY[ficha];
    }

    int dx = xCelda - xOrigen;
    int dy = yCelda - yOrigen;

    if(ficha<5 || ficha==7) //Peones, Caballo o Rey
    {
        if( ficha<4 && color && (dy!=-1 || abs(dx)>1 )) return false; //Peon blanco
        if( ficha<4 && !color && (dy!=1 || abs(dx)>1 )) return false;//Peon negro
        if( ficha==4 && ( abs(dx)+abs(dy)!=3 || dx==0 || dy==0 )) return false; //Caballo
        if( ficha==7 && ( abs(dx)>1 || abs(dy)>1) ) return false; //Rey

        ctmp=estado[yCelda][xCelda];

        if(ctmp!=' ')
        {
            if(ficha<4 && dx==0) return false; //El peon no puede comer de frente

            if(ctmp>97) return color;
            else return !color;
        }
        else
        {
            if(ficha<4 && dx!=0) return false; //El peon no puede avanzar en diagonal si no es comiendo

            return true;
        }
    }
    if(ficha==5 || ficha==6) //Alfil o Reina
    {
        if(abs(dx)==abs(dy))
        {
            xx = dx>0? 1 : -1;
            yy = dy>0? 1 : -1;
        }
        else if (dx==0 || dy==0)
        {
            if(ficha==5) return false; //El alfil no se puede mover de frente

            xx = dx==0? 0 : dx>0? 1 : -1;
            yy = dy==0? 0 : dy>0? 1 : -1;
        }
        else
        {
            return false;
        }

        cont=1;

        while (true)
        {
            ctmp=estado[yOrigen + yy*cont][xOrigen + xx*cont];

            if ((xOrigen + xx*cont == xCelda) && (yOrigen + yy*cont == yCelda))
            {
                if(ctmp!=' ')
                {
                    if(ctmp>97) return color;
                    else return !color;
                }
                else
                {
                    return true;
                }
            }
            else
            {
                if(ctmp!=' ') return false;
            }
            cont++;
        }
    }

    return false;
}

bool Ventana::movimientoValido(int ficha, bool color, int xCelda, int yCelda)
{
    return sePuedeMoverFicha(ficha,color,xCelda,yCelda);
}

void Ventana::matarFicha(int ficha, bool color)
{
    if(color)
    {
        posBlancasX[ficha]=-1;
        posBlancasY[ficha]=-1;
    }
    else
    {
        posNegrasX[ficha]=-1;
        posNegrasY[ficha]=-1;
    }

    tablerito->eliminarFicha(ficha,color);
}
