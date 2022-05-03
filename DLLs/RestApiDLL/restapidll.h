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
    int GetServerSatus();
    bool VerifyPIN(int Cardnumber, int PIN);
    bool CardHolderData(int Cardnumber, QJsonDocument *data);
    bool checkBalance(int CardNumber, double *balance);
    bool Withdraw(int sum, int CardNumber);
    ~RestApiDLL();
private:
    QNetworkAccessManager * getManager;
    QNetworkAccessManager * postManager;
    QNetworkReply *reply;
    QByteArray  response_data;

};

#endif // RESTAPIDLL_H
