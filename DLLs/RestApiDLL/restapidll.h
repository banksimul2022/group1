#ifndef RESTAPIDLL_H
#define RESTAPIDLL_H

#include "RestApiDLL_global.h"
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QString>



class RESTAPIDLL_EXPORT RestApiDLL : public QObject
{
    Q_OBJECT

public:
    RestApiDLL();
    bool VerifyPIN(QString Cardnumber, QString PIN);
    bool CardHolderData(QString Cardnumber, QJsonDocument *data);
    bool checkBalance(QString CardNumber, double *balance);
    bool Withdraw(QString sum, QString CardNumber);
    ~RestApiDLL();
private:
    QNetworkAccessManager * getManager;
    QNetworkAccessManager * withdrawManager;
    QNetworkAccessManager * PINManager;
    QNetworkAccessManager * balanceManager;
    QNetworkAccessManager * CardDataManager;
    QNetworkReply *reply;
    QNetworkReply *withdrawreply;
    QByteArray  response_data;
};

#endif // RESTAPIDLL_H
