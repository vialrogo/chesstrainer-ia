/**
  Proyecto 2 IA: ChessTrainer
  Erika Suarez Valencia
  Victor Alberto Romero
*/

#include <QtGui/QApplication>
#include <QTextCodec>
#include "Ventana.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    // Para poder colocar acentos en la aplicación
    QTextCodec *linuxCodec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(linuxCodec);
    QTextCodec::setCodecForCStrings(linuxCodec);
    QTextCodec::setCodecForLocale(linuxCodec);

    //QApplication
    QApplication a(argc, argv);
    Ventana w;

    w.show();

    return a.exec();
}
