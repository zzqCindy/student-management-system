/********************************************************************************
** Form generated from reading UI file 'addstudent.ui'
**
** Created: Mon Aug 29 20:28:03 2016
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDSTUDENT_H
#define UI_ADDSTUDENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddStudent
{
public:
    QPushButton *ok;
    QPushButton *cancel;
    QLabel *label;
    QComboBox *mNumber;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *cYear;
    QComboBox *cNumber;

    void setupUi(QDialog *AddStudent)
    {
        if (AddStudent->objectName().isEmpty())
            AddStudent->setObjectName(QString::fromUtf8("AddStudent"));
        AddStudent->resize(400, 300);
        ok = new QPushButton(AddStudent);
        ok->setObjectName(QString::fromUtf8("ok"));
        ok->setGeometry(QRect(100, 210, 75, 23));
        cancel = new QPushButton(AddStudent);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setGeometry(QRect(210, 210, 75, 23));
        label = new QLabel(AddStudent);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 50, 54, 21));
        mNumber = new QComboBox(AddStudent);
        mNumber->setObjectName(QString::fromUtf8("mNumber"));
        mNumber->setGeometry(QRect(200, 50, 75, 22));
        label_2 = new QLabel(AddStudent);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(110, 100, 54, 21));
        label_3 = new QLabel(AddStudent);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 150, 54, 21));
        cYear = new QComboBox(AddStudent);
        cYear->setObjectName(QString::fromUtf8("cYear"));
        cYear->setGeometry(QRect(200, 100, 75, 22));
        cNumber = new QComboBox(AddStudent);
        cNumber->setObjectName(QString::fromUtf8("cNumber"));
        cNumber->setGeometry(QRect(200, 150, 75, 22));

        retranslateUi(AddStudent);

        QMetaObject::connectSlotsByName(AddStudent);
    } // setupUi

    void retranslateUi(QDialog *AddStudent)
    {
        AddStudent->setWindowTitle(QApplication::translate("AddStudent", "Dialog", 0, QApplication::UnicodeUTF8));
        ok->setText(QApplication::translate("AddStudent", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        cancel->setText(QApplication::translate("AddStudent", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddStudent", "\344\270\223\344\270\232\344\273\243\345\217\267", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddStudent", "\345\205\245\345\255\246\345\271\264\344\273\275", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AddStudent", "\347\217\255\345\210\253", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddStudent: public Ui_AddStudent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDSTUDENT_H
