/********************************************************************************
** Form generated from reading UI file 'compuldetail.ui'
**
** Created: Mon Aug 29 20:28:03 2016
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPULDETAIL_H
#define UI_COMPULDETAIL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CompulDetail
{
public:

    void setupUi(QDialog *CompulDetail)
    {
        if (CompulDetail->objectName().isEmpty())
            CompulDetail->setObjectName(QString::fromUtf8("CompulDetail"));
        CompulDetail->resize(400, 300);

        retranslateUi(CompulDetail);

        QMetaObject::connectSlotsByName(CompulDetail);
    } // setupUi

    void retranslateUi(QDialog *CompulDetail)
    {
        CompulDetail->setWindowTitle(QApplication::translate("CompulDetail", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CompulDetail: public Ui_CompulDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPULDETAIL_H
