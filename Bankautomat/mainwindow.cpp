#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dllSerialPort(new DLLSerialPort)
{
    ui->setupUi(this);
   // ui->pushButton->setVisible(false);
   // ui->lineEditPin->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RFID_INPUT_OK() {

   // ui->labelResult_2->setText("Kortti luettu");
   // ui->pushButton->setVisible(true);
   // ui->lineEditPin->setVisible(true);
    }










void MainWindow::on_pushButton_clicked()
{
  //  QString pin=ui->lineEditPin->text();


}

