#include "enterpin.h"
#include "ui_enterpin.h"

EnterPin::EnterPin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EnterPin)
{
    ui->setupUi(this);
}

EnterPin::~EnterPin()
{
    delete ui;
}
