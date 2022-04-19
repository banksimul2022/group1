#include "mainwindow.h"
#include <QDebug>

#include <QApplication>
#include <QLibrary>
QLibrary lib("DLLPinCode.dll");

#ifndef RFID_LIB_H
   #define KorttiEiLukijassa() false
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();




    while(KorttiEiLukijassa()){
        a.processEvents();


    }

    w.on_RFID_INPUT_OK();
    //UI_pin.show();





    return a.exec();
}
