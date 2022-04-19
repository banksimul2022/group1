#include "kirjautuminen.h"
#include "ui_kirjautuminen.h"

#ifndef RFID_LIB_INSTALLED
   #define korttiLukijassa() false
#endif

kirjautuminen::kirjautuminen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kirjautuminen)
{
    ui->setupUi(this);
}

kirjautuminen::~kirjautuminen()
{
    delete ui;
}
