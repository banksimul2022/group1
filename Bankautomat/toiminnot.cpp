#include "toiminnot.h"
#include "ui_toiminnot.h"
#include <QDebug>
#include "mainwindow.h"
#include <QString>

Toiminnot::Toiminnot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Toiminnot)

{
    RestApiDLL2 = new RestApiDLL();
    ui->setupUi(this);
    ui->label->setVisible(false);
    ui->lineEditSumma->setVisible(false);
    ui->label_2->setVisible(false);
    ui->pushButtonTakaisin->setVisible(false);
    ui->pushButtonOk->setVisible(false);
    ui->pushButtonTakaisin2->setVisible(false);
    ui->labelSaldoWithdraw->setVisible(false);

}

Toiminnot::~Toiminnot()
{
    delete ui;
}

void Toiminnot::on_pushButtonSaldo_clicked()
{
    double balance = 0;
    QString balancestring = QString::number(balance);
    bool balanceCheck_ok = false;
    qDebug() << "extern ID on : " << ID;
    balanceCheck_ok = RestApiDLL2->checkBalance(ID, &balance);
    if(balanceCheck_ok) {
        //näytä saldo käyttäjälle
        ui->labelSaldo->setText(balancestring);


    }
    else {
        //tulosta virhe käyttäjälle
    }
    ui->pushButtonSaldo->setVisible(false);
    ui->label->setVisible(true);
    ui->pushButtonTakaisin->setVisible(true);
    ui->pushButtonNosto->setVisible(false);
    ui->pushButtonTakaisin2->setVisible(false);



}


void Toiminnot::on_pushButtonNosto_clicked()
{

    ui->pushButtonSaldo->setVisible(false);
    ui->pushButtonNosto->setVisible(false);
    ui->label_2->setVisible(true);
    ui->lineEditSumma->setVisible(true);
    ui->pushButtonOk->setVisible(true);
    ui->pushButtonTakaisin2->setVisible(true);

}


void Toiminnot::on_pushButtonTakaisin_clicked()
{
    ui->pushButtonNosto->setVisible(true);
    ui->pushButtonSaldo->setVisible(true);
    ui->label->setVisible(false);
    ui->pushButtonTakaisin->setVisible(false);
    ui->labelSaldoWithdraw->setVisible(false);
    ui->labelSaldo->setVisible(false);
}


void Toiminnot::on_pushButtonOk_clicked()
{
    //restapi withdraw
     bool balanceCheck_ok = false;
     double balance = 0;
     bool withdraw_ok;
     QString balancestring = QString::number(balance);
     QString Summa=ui->lineEditSumma->text();
     withdraw_ok = RestApiDLL2->Withdraw(Summa, ID);
     withdraw_ok =true;
     if (withdraw_ok) {
         balanceCheck_ok = RestApiDLL2->checkBalance(ID, &balance);
         balanceCheck_ok = true;
         if(balanceCheck_ok) {
             //näytä saldo käyttäjälle
             ui->labelSaldo->setText(balancestring);
             ui->labelUusiSaldoWithdraw->setVisible(true);
             qDebug() << "tehdään jotaki";
             ui->labelSaldoWithdraw->setVisible(true);


         }
         else {
             //tulosta virhe käyttäjälle
         }

     }
     else {
         //Tulosta virhe
     }


}


void Toiminnot::on_pushButtonTakaisin2_clicked()
{
    ui->pushButtonNosto->setVisible(true);
    ui->pushButtonSaldo->setVisible(true);
    ui->label_2->setVisible(false);
    ui->lineEditSumma->setVisible(false);
    ui->pushButtonOk->setVisible(false);
    ui->pushButtonTakaisin2->setVisible(false);
}

