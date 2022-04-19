#ifndef ENTERPIN_H
#define ENTERPIN_H

#include <QDialog>

namespace Ui {
class EnterPin;
}

class EnterPin : public QDialog
{
    Q_OBJECT

public:
    explicit EnterPin(QWidget *parent = nullptr);
    ~EnterPin();

private:
    Ui::EnterPin *ui;
};

#endif // ENTERPIN_H
