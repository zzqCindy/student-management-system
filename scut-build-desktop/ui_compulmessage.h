/********************************************************************************
** Form generated from reading UI file 'compulmessage.ui'
**
** Created: Mon Aug 29 20:28:03 2016
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPULMESSAGE_H
#define UI_COMPULMESSAGE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CompulMessage
{
public:

    void setupUi(QDialog *CompulMessage)
    {
        if (CompulMessage->objectName().isEmpty())
            CompulMessage->setObjectName(QString::fromUtf8("CompulMessage"));
        CompulMessage->resize(400, 300);

        retranslateUi(CompulMessage);

        QMetaObject::connectSlotsByName(CompulMessage);
    } // setupUi

    void retranslateUi(QDialog *CompulMessage)
    {
        CompulMessage->setWindowTitle(QApplication::translate("CompulMessage", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CompulMessage: public Ui_CompulMessage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPULMESSAGE_H
