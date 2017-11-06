/********************************************************************************
** Form generated from reading UI file 'changepassword.ui'
**
** Created: Mon Aug 29 20:28:03 2016
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEPASSWORD_H
#define UI_CHANGEPASSWORD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChangePassword
{
public:
    QLabel *label;
    QLineEdit *oldPassword;
    QLabel *label_2;
    QLineEdit *newPassword;
    QLabel *label_3;
    QLineEdit *surePassword;
    QPushButton *yes;
    QPushButton *cancel;

    void setupUi(QDialog *ChangePassword)
    {
        if (ChangePassword->objectName().isEmpty())
            ChangePassword->setObjectName(QString::fromUtf8("ChangePassword"));
        ChangePassword->resize(400, 300);
        label = new QLabel(ChangePassword);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 60, 54, 21));
        oldPassword = new QLineEdit(ChangePassword);
        oldPassword->setObjectName(QString::fromUtf8("oldPassword"));
        oldPassword->setGeometry(QRect(180, 60, 113, 20));
        label_2 = new QLabel(ChangePassword);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 110, 54, 21));
        newPassword = new QLineEdit(ChangePassword);
        newPassword->setObjectName(QString::fromUtf8("newPassword"));
        newPassword->setGeometry(QRect(180, 110, 113, 20));
        label_3 = new QLabel(ChangePassword);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 160, 54, 21));
        surePassword = new QLineEdit(ChangePassword);
        surePassword->setObjectName(QString::fromUtf8("surePassword"));
        surePassword->setGeometry(QRect(180, 160, 113, 20));
        yes = new QPushButton(ChangePassword);
        yes->setObjectName(QString::fromUtf8("yes"));
        yes->setGeometry(QRect(100, 220, 75, 23));
        cancel = new QPushButton(ChangePassword);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setGeometry(QRect(220, 220, 75, 23));

        retranslateUi(ChangePassword);

        QMetaObject::connectSlotsByName(ChangePassword);
    } // setupUi

    void retranslateUi(QDialog *ChangePassword)
    {
        ChangePassword->setWindowTitle(QApplication::translate("ChangePassword", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ChangePassword", "\345\216\237\345\247\213\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ChangePassword", "\346\226\260\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ChangePassword", "\347\241\256\350\256\244\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        yes->setText(QApplication::translate("ChangePassword", "\347\241\256\350\256\244", 0, QApplication::UnicodeUTF8));
        cancel->setText(QApplication::translate("ChangePassword", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChangePassword: public Ui_ChangePassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEPASSWORD_H
