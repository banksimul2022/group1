#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dllSerialPort(new DLLSerialPort)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dllSerialPort;
}
