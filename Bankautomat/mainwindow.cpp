#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "toiminnot.h"


QString ID;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RestApi = new RestApiDLL();
    ui->label_3->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    ui->label_3->setVisible(false);
    bool pinOK = false;
    ID = ui->lineEditID->text();
    QString PIN = ui->lineEditPIN->text();
    pinOK = RestApi->VerifyPIN(ID,PIN);
    ui->lineEditID->clear();
    ui->lineEditPIN->clear();

    if (pinOK){
        Toiminnot toiminnot1;
        toiminnot1.setModal(true);
        toiminnot1.exec();

    }
    else {
    ui->label_3->setVisible(true);
    }

}

