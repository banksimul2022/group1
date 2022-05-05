#ifndef TOIMINNOT_H
#define TOIMINNOT_H

#include <QDialog>
#include "restapidll.h"

extern QString ID;

namespace Ui {
class Toiminnot;
}

class Toiminnot : public QDialog
{
    Q_OBJECT

public:
    explicit Toiminnot(QWidget *parent = nullptr);
    ~Toiminnot();

private slots:
    void on_pushButtonSaldo_clicked();

    void on_pushButtonNosto_clicked();

    void on_pushButtonTakaisin_clicked();

    void on_pushButtonOk_clicked();

    void on_pushButtonTakaisin2_clicked();

private:
    Ui::Toiminnot *ui;
    RestApiDLL *RestApiDLL2;
};

#endif // TOIMINNOT_H
