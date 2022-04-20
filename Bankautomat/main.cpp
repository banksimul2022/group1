#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QLibrary>
#include "DLLs/DLLPinCode/DLLPinCode/kirjautuminen.h"

#ifndef RFID_LIB_H
   #define kirjautuminenValmis() false
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    kirjautuminen login;



    while(kirjautuminenValmis()){
        a.processEvents();


    }

    w.on_RFID_INPUT_OK();
    //UI_pin.show();





    return a.exec();
}
