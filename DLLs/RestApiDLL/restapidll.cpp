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
    postManager = new QNetworkAccessManager(this);
    qDebug() << "RestApi started" << Qt::endl;
}


/*
int RestApiDLL::GetServerSatus()
{
    QEventLoop loop;
    QString site_url="http://localhost:3000/test";
    QNetworkRequest request((site_url));
    reply = getManager->get(request);
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit); //wait for finished reply
    loop.exec();
    response_data=reply->readAll();
    return 0;
}
*/



bool RestApiDLL::VerifyPIN(int Cardnumber, int PIN)
{
    QEventLoop loop;
    QString Cardstring = QVariant(Cardnumber).toString();
    QString PINstring = QVariant(PIN).toString();

    QUrl URL("http://localhost:3000/kortti/kortteja");
    QNetworkRequest request(URL);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem ("Korttinumero", Cardstring);
    urlQuery.addQueryItem ("PIN", PINstring);

    reply = postManager->post(request, urlQuery.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit); //wait for finished reply
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {

        response_data=reply->readAll();


        //qDebug()<<"DATA : "+response_data;
        QJsonDocument json_Doc = QJsonDocument::fromJson(response_data);
        bool pincorrect =  json_Doc.object().value("success").toBool();

        reply->deleteLater();
        postManager->deleteLater();

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

bool RestApiDLL::CardHolderData(int Cardnumber, QJsonDocument *data)
{
    QEventLoop loop;
    QString Cardstring = QVariant(Cardnumber).toString();

    QUrl URL("http://localhost:3000/toiminnot/card_data");
    QNetworkRequest request(URL);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem ("Korttinumero", Cardstring);

    reply = postManager->post(request, urlQuery.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit); //wait for finished reply
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {

        response_data=reply->readAll();


        //qDebug()<<"DATA : "+response_data;
        QJsonDocument json_Doc = QJsonDocument::fromJson(response_data);
        bool query_ok =  json_Doc.object().value("success").toBool();

        reply->deleteLater();
        postManager->deleteLater();

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

bool RestApiDLL::checkBalance(int Cardnumber, double *balance)
{

    QEventLoop loop;
    QString Cardstring = QVariant(Cardnumber).toString();


    QUrl URL("http://localhost:3000/toiminnot/balance");
    QNetworkRequest request(URL);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem ("Korttinumero", Cardstring);


    reply = postManager->post(request, urlQuery.toString(QUrl::FullyEncoded).toUtf8());
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
        postManager->deleteLater();

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


bool RestApiDLL::Withdraw(int sum, int CardNumber)
{
    QEventLoop loop;
    QString Cardstring = QVariant(CardNumber).toString();
    QString SUMstring = QVariant(sum).toString();

    QUrl URL("http://localhost:3000/toiminnot/nosto");
    QNetworkRequest request(URL);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery urlQuery;
    urlQuery.addQueryItem ("Korttinumero", Cardstring);
    urlQuery.addQueryItem ("rahasumma", SUMstring);

    reply = postManager->post(request, urlQuery.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit); //wait for finished reply
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        reply->deleteLater();
        postManager->deleteLater();
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
