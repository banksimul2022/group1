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
        reply->deleteLater();
        postManager->deleteLater();

        qDebug()<<"DATA : "+response_data;
        QJsonDocument json_Doc = QJsonDocument::fromJson(response_data);
        bool pincorrect =  json_Doc.object().value("pin").toBool();

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

int RestApiDLL::Withdraw(int sum, int CardNumber)
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
        return 1;
    }




    return 1;
}


RestApiDLL::~RestApiDLL()
{
    qDebug()<<"RestApiDLL destroyed";
}
