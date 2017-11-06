/********************************************************************************
** Form generated from reading UI file 'grade.ui'
**
** Created: Thu Aug 11 18:21:02 2016
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRADE_H
#define UI_GRADE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Grade
{
public:
    QComboBox *Year;
    QComboBox *Term;
    QComboBox *Class;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QTableWidget *GradeTable;

    void setupUi(QDialog *Grade)
    {
        if (Grade->objectName().isEmpty())
            Grade->setObjectName(QString::fromUtf8("Grade"));
        Grade->resize(662, 501);
        Year = new QComboBox(Grade);
        Year->setObjectName(QString::fromUtf8("Year"));
        Year->setGeometry(QRect(90, 90, 75, 22));
        Term = new QComboBox(Grade);
        Term->setObjectName(QString::fromUtf8("Term"));
        Term->setGeometry(QRect(250, 90, 75, 22));
        Class = new QComboBox(Grade);
        Class->setObjectName(QString::fromUtf8("Class"));
        Class->setGeometry(QRect(430, 90, 75, 22));
        label = new QLabel(Grade);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 90, 54, 16));
        label_2 = new QLabel(Grade);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(200, 90, 54, 21));
        label_3 = new QLabel(Grade);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(360, 90, 54, 21));
        GradeTable = new QTableWidget(Grade);
        if (GradeTable->columnCount() < 9)
            GradeTable->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        GradeTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        GradeTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        GradeTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        GradeTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        GradeTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        GradeTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        GradeTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        GradeTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        GradeTable->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        GradeTable->setObjectName(QString::fromUtf8("GradeTable"));
        GradeTable->setGeometry(QRect(30, 150, 601, 331));

        retranslateUi(Grade);

        QMetaObject::connectSlotsByName(Grade);
    } // setupUi

    void retranslateUi(QDialog *Grade)
    {
        Grade->setWindowTitle(QApplication::translate("Grade", "Dialog", 0, QApplication::UnicodeUTF8));
        Year->clear();
        Year->insertItems(0, QStringList()
         << QApplication::translate("Grade", "2015-2016", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Grade", "2014-2015", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Grade", "2013-2014", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Grade", "2012-2013", 0, QApplication::UnicodeUTF8)
        );
        Term->clear();
        Term->insertItems(0, QStringList()
         << QApplication::translate("Grade", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Grade", "2", 0, QApplication::UnicodeUTF8)
        );
        Class->clear();
        Class->insertItems(0, QStringList()
         << QApplication::translate("Grade", "\345\277\205\344\277\256\350\257\276", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Grade", "\351\200\211\344\277\256\350\257\276", 0, QApplication::UnicodeUTF8)
        );
        label->setText(QApplication::translate("Grade", "\345\255\246\345\271\264", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Grade", "\345\255\246\346\234\237", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Grade", "\350\257\276\347\250\213\346\200\247\350\264\250", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = GradeTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("Grade", "\345\255\246\345\271\264", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = GradeTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("Grade", "\345\255\246\346\234\237", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = GradeTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("Grade", "\350\257\276\347\250\213\344\273\243\347\240\201", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = GradeTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("Grade", "\350\257\276\347\250\213\345\220\215\345\255\227", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = GradeTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("Grade", "\350\257\276\347\250\213\345\261\236\346\200\247", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = GradeTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("Grade", "\345\255\246\345\210\206", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = GradeTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("Grade", "\347\273\251\347\202\271", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = GradeTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("Grade", "\346\210\220\347\273\251", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem8 = GradeTable->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("Grade", "\346\216\222\345\220\215", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Grade: public Ui_Grade {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRADE_H
