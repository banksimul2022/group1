#ifndef KIRJAUTUMINEN_H
#define KIRJAUTUMINEN_H

#include <QDialog>

namespace Ui {
class kirjautuminen;
}

class kirjautuminen : public QDialog
{
    Q_OBJECT

public:
    explicit kirjautuminen(QWidget *parent = nullptr);
    ~kirjautuminen();

private:
    Ui::kirjautuminen *ui;
};

#endif // KIRJAUTUMINEN_H
