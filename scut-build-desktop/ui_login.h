/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created: Mon Aug 29 20:28:03 2016
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *label;
    QLineEdit *UserName;
    QLabel *label_2;
    QLineEdit *Password;
    QPushButton *login;
    QPushButton *exit;
    QComboBox *comboBox;
    QLabel *label_3;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QString::fromUtf8("Login"));
        Login->resize(400, 300);
        label = new QLabel(Login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 120, 54, 21));
        UserName = new QLineEdit(Login);
        UserName->setObjectName(QString::fromUtf8("UserName"));
        UserName->setGeometry(QRect(190, 120, 113, 20));
        label_2 = new QLabel(Login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 160, 54, 21));
        Password = new QLineEdit(Login);
        Password->setObjectName(QString::fromUtf8("Password"));
        Password->setGeometry(QRect(190, 160, 113, 20));
        login = new QPushButton(Login);
        login->setObjectName(QString::fromUtf8("login"));
        login->setGeometry(QRect(80, 230, 75, 23));
        exit = new QPushButton(Login);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setGeometry(QRect(220, 230, 75, 23));
        comboBox = new QComboBox(Login);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(190, 80, 75, 22));
        label_3 = new QLabel(Login);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(90, 82, 54, 20));

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Login", "\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Login", "\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        Password->setText(QString());
        login->setText(QApplication::translate("Login", "\347\231\273\345\275\225", 0, QApplication::UnicodeUTF8));
        exit->setText(QApplication::translate("Login", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Login", "\347\256\241\347\220\206\345\221\230", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Login", "\350\200\201\345\270\210", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Login", "\345\255\246\347\224\237", 0, QApplication::UnicodeUTF8)
        );
        label_3->setText(QApplication::translate("Login", "\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
