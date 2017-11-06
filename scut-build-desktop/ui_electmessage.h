/********************************************************************************
** Form generated from reading UI file 'electmessage.ui'
**
** Created: Mon Aug 29 20:28:03 2016
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ELECTMESSAGE_H
#define UI_ELECTMESSAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ElectMessage
{
public:

    void setupUi(QDialog *ElectMessage)
    {
        if (ElectMessage->objectName().isEmpty())
            ElectMessage->setObjectName(QString::fromUtf8("ElectMessage"));
        ElectMessage->resize(400, 300);

        retranslateUi(ElectMessage);

        QMetaObject::connectSlotsByName(ElectMessage);
    } // setupUi

    void retranslateUi(QDialog *ElectMessage)
    {
        ElectMessage->setWindowTitle(QApplication::translate("ElectMessage", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ElectMessage: public Ui_ElectMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ELECTMESSAGE_H
