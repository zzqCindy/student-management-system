/********************************************************************************
** Form generated from reading UI file 'addcourse.ui'
**
** Created: Mon Aug 29 20:28:03 2016
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCOURSE_H
#define UI_ADDCOURSE_H

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

class Ui_AddCourse
{
public:
    QLineEdit *courseName;
    QComboBox *courseType;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *studentNumber;
    QComboBox *credit;
    QComboBox *classTime;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QComboBox *classWeek;

    void setupUi(QDialog *AddCourse)
    {
        if (AddCourse->objectName().isEmpty())
            AddCourse->setObjectName(QString::fromUtf8("AddCourse"));
        AddCourse->resize(457, 348);
        courseName = new QLineEdit(AddCourse);
        courseName->setObjectName(QString::fromUtf8("courseName"));
        courseName->setGeometry(QRect(160, 40, 113, 20));
        courseType = new QComboBox(AddCourse);
        courseType->setObjectName(QString::fromUtf8("courseType"));
        courseType->setGeometry(QRect(160, 80, 75, 22));
        label = new QLabel(AddCourse);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 40, 54, 16));
        label_2 = new QLabel(AddCourse);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 80, 54, 21));
        label_3 = new QLabel(AddCourse);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 120, 54, 21));
        label_4 = new QLabel(AddCourse);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(80, 160, 54, 21));
        label_5 = new QLabel(AddCourse);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(70, 200, 51, 21));
        label_6 = new QLabel(AddCourse);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(270, 200, 54, 21));
        studentNumber = new QLineEdit(AddCourse);
        studentNumber->setObjectName(QString::fromUtf8("studentNumber"));
        studentNumber->setGeometry(QRect(160, 120, 113, 20));
        credit = new QComboBox(AddCourse);
        credit->setObjectName(QString::fromUtf8("credit"));
        credit->setGeometry(QRect(160, 160, 75, 22));
        classTime = new QComboBox(AddCourse);
        classTime->setObjectName(QString::fromUtf8("classTime"));
        classTime->setGeometry(QRect(320, 200, 75, 22));
        pushButton = new QPushButton(AddCourse);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(90, 270, 75, 23));
        pushButton_2 = new QPushButton(AddCourse);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(250, 270, 75, 23));
        classWeek = new QComboBox(AddCourse);
        classWeek->setObjectName(QString::fromUtf8("classWeek"));
        classWeek->setGeometry(QRect(160, 200, 75, 22));

        retranslateUi(AddCourse);

        QMetaObject::connectSlotsByName(AddCourse);
    } // setupUi

    void retranslateUi(QDialog *AddCourse)
    {
        AddCourse->setWindowTitle(QApplication::translate("AddCourse", "Dialog", 0, QApplication::UnicodeUTF8));
        courseType->clear();
        courseType->insertItems(0, QStringList()
         << QApplication::translate("AddCourse", "\345\277\205\344\277\256\350\257\276", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "\351\200\211\344\277\256\350\257\276", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("AddCourse", "\350\257\276\347\250\213\345\220\215\345\255\227", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddCourse", "\350\257\276\347\250\213\346\200\247\350\264\250", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AddCourse", "\345\255\246\347\224\237\344\272\272\346\225\260", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AddCourse", "\345\255\246\345\210\206", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("AddCourse", "\344\270\212\350\257\276\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("AddCourse", "\350\212\202\346\225\260", 0, QApplication::UnicodeUTF8));
        credit->clear();
        credit->insertItems(0, QStringList()
         << QApplication::translate("AddCourse", "1.0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "2.0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "3.0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "4.0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "5.0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "6.0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "7.0", 0, QApplication::UnicodeUTF8)
        );
        classTime->clear();
        classTime->insertItems(0, QStringList()
         << QApplication::translate("AddCourse", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "5", 0, QApplication::UnicodeUTF8)
        );
        pushButton->setText(QApplication::translate("AddCourse", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("AddCourse", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
        classWeek->clear();
        classWeek->insertItems(0, QStringList()
         << QApplication::translate("AddCourse", "\346\230\237\346\234\237\344\270\200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "\346\230\237\346\234\237\344\272\214", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "\346\230\237\346\234\237\344\270\211", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "\346\230\237\346\234\237\345\233\233", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "\346\230\237\346\234\237\344\272\224", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "\346\230\237\346\234\237\345\205\255", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("AddCourse", "\346\230\237\346\234\237\345\244\251", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class AddCourse: public Ui_AddCourse {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCOURSE_H
