#include "toiminnot.h"
#include "ui_toiminnot.h"
#include <QDebug>
#include "mainwindow.h"
#include <QString>
#include <QVariant>
#include <QJsonDocument>

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

    bool CardHolderData_ok = false;
    QJsonDocument HolderData;
    CardHolderData_ok = RestApiDLL2->CardHolderData(ID, &HolderData);
    if (CardHolderData_ok) {
        qDebug() << "Kortin omistajan tiedot: " << HolderData;
        QString Omistajannimi = HolderData.object().value("Nimi").toString();
        QString OmistajanOsoite = HolderData.object().value("Osoite").toString();
        qDebug() << "Omistajan nimi: " << Omistajannimi;
        qDebug() << "Omistajan nimi: " << OmistajanOsoite;
        ui->labelOmistajanNimi->setText(Omistajannimi);
        ui->labelOmistajanOsoite->setText(OmistajanOsoite);

    }
    else {
        //Tulostaa että kortin omistajan tietoja ei saatu
        ui->labelOmistajanNimi->setText("Kortin omistajan tietoja ei saatu");
    }

}

Toiminnot::~Toiminnot()
{
    delete ui;
}

void Toiminnot::on_pushButtonSaldo_clicked()
{
    double balance = 0;
    bool balanceCheck_ok = false;
    qDebug() << "extern ID on : " << ID;
    balanceCheck_ok = RestApiDLL2->checkBalance(ID, &balance);
    if(balanceCheck_ok) {
        //näytä saldo käyttäjälle
        QString balancestring = QVariant(balance).toString();
        qDebug() <<"saldostring"<<balancestring;
        qDebug() <<"saldos"<<balance;
        ui->labelSaldo->setText(balancestring);
        ui->labelSaldo->setVisible(true);
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
     QString Summa=ui->lineEditSumma->text();
     withdraw_ok = RestApiDLL2->Withdraw(Summa, ID);
     if (withdraw_ok) {
         balanceCheck_ok = RestApiDLL2->checkBalance(ID, &balance);
         if(balanceCheck_ok) {
             //näytä saldo käyttäjälle
             QString balancestring = QVariant(balance).toString();
             ui->labelUusiSaldoWithdraw->setText(balancestring);
             ui->labelSaldoWithdraw->setText("Saldosi noston jälkeen");
             ui->labelUusiSaldoWithdraw->setVisible(true);
             ui->labelSaldoWithdraw->setVisible(true);
         }
         else {
             //tulosta virhe käyttäjälle
         }

     }
     else {
         //Tulosta virhe
         qDebug() <<"asddadsadas";
         ui->labelSaldoWithdraw->setVisible(true);
         ui->labelUusiSaldoWithdraw->setVisible(false);
         ui->labelSaldoWithdraw->setText("Rahat eivät riittäneet");

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
    ui->labelSaldoWithdraw->setVisible(false);
    ui->labelUusiSaldoWithdraw->setVisible(false);

}

