/********************************************************************************
** Form generated from reading UI file 'enterpin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTERPIN_H
#define UI_ENTERPIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_EnterPin
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *EnterPin)
    {
        if (EnterPin->objectName().isEmpty())
            EnterPin->setObjectName(QString::fromUtf8("EnterPin"));
        EnterPin->resize(654, 555);
        buttonBox = new QDialogButtonBox(EnterPin);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(140, 430, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(EnterPin);
        QObject::connect(buttonBox, SIGNAL(accepted()), EnterPin, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), EnterPin, SLOT(reject()));

        QMetaObject::connectSlotsByName(EnterPin);
    } // setupUi

    void retranslateUi(QDialog *EnterPin)
    {
        EnterPin->setWindowTitle(QCoreApplication::translate("EnterPin", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EnterPin: public Ui_EnterPin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTERPIN_H
