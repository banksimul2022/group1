#include "mainwindow.h"
#include "enterpin.h"

#include <QApplication>

#ifndef RFID_LIB_H
   #define KorttiEiLukijassa() false
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    EnterPin UI_pin;
    w.show();


    while(KorttiEiLukijassa()){
        a.processEvents();


    }

    w.on_RFID_INPUT_OK();
    //UI_pin.show();





    return a.exec();
}
