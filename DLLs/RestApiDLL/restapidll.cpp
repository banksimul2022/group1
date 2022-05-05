#include "restapidll.h"
#include <QDebug>
#include <QUrlQuery>
#include <QVariant>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QJsonArray>


RestApiDLL::RestApiDLL()
{

    getManager = new QNetworkAccessManager(this);
    qDebug() << "RestApi started" << Qt::endl;
}

bool RestApiDLL::VerifyPIN(QString Cardstring, QString PINstring)
{
    PINManager = new QNetworkAccessManager(this);
    QEventLoop loop;

    //ei tarvita koska mainwindow antaa jo string muotoisena
    //QString Cardstring = QVariant(Cardnumber).toString();
    //QString PINstring = QVariant(PIN).toString();

    QUrl URL("http://localhost:3000/kortti/kortteja");
    QNetworkRequest request(URL);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem ("Korttinumero", Cardstring);
    urlQuery.addQueryItem ("PIN", PINstring);

    reply = PINManager->post(request, urlQuery.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit); //wait for finished reply
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {

        response_data=reply->readAll();
        //qDebug()<<"DATA : "+response_data;
        QJsonDocument json_Doc = QJsonDocument::fromJson(response_data);
        bool pincorrect =  json_Doc.object().value("success").toBool();

        reply->deleteLater();
        PINManager->deleteLater();

        if ( pincorrect == true)
        {

            qDebug() << "success, pin and card are valid";
            return true;
        }
        else
        {
            qDebug() << "pin and card are invalid";
            return false;
        }

    }

    else
    {
        return false; //return error
    }
}

bool RestApiDLL::CardHolderData(QString Cardstring, QJsonDocument *data)
{
    CardDataManager = new QNetworkAccessManager(this);

    QEventLoop loop;
    //QString Cardstring = QVariant(Cardnumber).toString();

    QUrl URL("http://localhost:3000/toiminnot/card_data");
    QNetworkRequest request(URL);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem ("Korttinumero", Cardstring);

    reply = CardDataManager->post(request, urlQuery.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit); //wait for finished reply
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {

        response_data=reply->readAll();


        //qDebug()<<"DATA : "+response_data;
        QJsonDocument json_Doc = QJsonDocument::fromJson(response_data);
        bool query_ok =  json_Doc.object().value("success").toBool();

        reply->deleteLater();
        CardDataManager->deleteLater();

        if ( query_ok == true)
        {

            qDebug() << "success";
            *data = json_Doc;
            return true;
        }
        else
        {
            qDebug() << "pin and card are invalid";
            return false;
        }

    }

    else
    {
        return false; //return error
    }
}

bool RestApiDLL::checkBalance(QString Cardstring, double *balance)
{
    balanceManager = new QNetworkAccessManager(this);

    QEventLoop loop;
    //QString Cardstring = QVariant(Cardnumber).toString();


    QUrl URL("http://localhost:3000/toiminnot/balance");
    QNetworkRequest request(URL);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem ("Korttinumero", Cardstring);


    reply = balanceManager->post(request, urlQuery.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit); //wait for finished reply
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {

        response_data=reply->readAll();


        //qDebug()<<"DATA : "+response_data;
        QJsonDocument json_Doc = QJsonDocument::fromJson(response_data);
        bool success =  json_Doc.object().value("success").toBool();
        *balance =  json_Doc.object().value("balance").toDouble();

        reply->deleteLater();
        //delete reply;
        balanceManager->deleteLater();

        if ( success == true)
        {

            return true;
        }
        else
        {

            qDebug() << "invalid card";
            return false;
        }

    }

    else
    {
        return false; //return error
    }
}


bool RestApiDLL::Withdraw(QString SUMstring, QString Cardstring) //palauttaa väärän responsen (muuten toimii)
{
    withdrawManager = new QNetworkAccessManager(this);

    QEventLoop loop;
    //QString Cardstring = QVariant(CardNumber).toString();
    //QString SUMstring = QVariant(sum).toString();

    QUrl URL("http://localhost:3000/toiminnot/nosto/simple");
    QNetworkRequest request(URL);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem ("Korttinumero", Cardstring);
    urlQuery.addQueryItem ("rahasumma", SUMstring);

    reply = withdrawManager->post(request, urlQuery.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit); //wait for finished reply
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        qDebug()<<"Withdrawal data : "+response_data;
        QJsonDocument json_Doc = QJsonDocument::fromJson(response_data);
        qDebug() << "json doc from withdrawal: " << json_Doc;
        bool success =  json_Doc.object().value("success").toBool();
        reply->deleteLater();
        withdrawManager->deleteLater();
        return success;

    }

    else
    {
        return false;
    }

    return false;
}


RestApiDLL::~RestApiDLL()
{
    qDebug()<<"RestApiDLL destroyed";
}
