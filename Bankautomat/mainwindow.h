#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DLLs/DLLSerialPort/DLLSerialPort/dllserialport.h"
#include <QDialog>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

  public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  void on_RFID_INPUT_OK();

  private slots:

  void on_pushButton_clicked();

  private:
  Ui::MainWindow* ui;
  DLLSerialPort* dllSerialPort;
};
#endif // MAINWINDOW_H
