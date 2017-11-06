#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QtGui>
#include "student.h"
#include <fstream>

namespace Ui {
    class Widget;
}
class QTabWidget;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(Student s, QWidget *parent = 0,
                    int i1 = 0,int i2 = 0,int i3 = 0,int bi = 0);
    void initTable2(QTableWidget *);
    void initTable3(QTableWidget *);
    void initTable4(QTableWidget *);
    void initTable5(QTableWidget *);
    void initInfWidget(QWidget *);
    void initWidget(QWidget *, QTableWidget *,int);
    void initChooseWidget(QWidget *, QTableWidget *);

    int findNumber(int classNumber,int studentNumber);
    ~Widget();

    Student student;

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void bClicked1();
    void bClicked2();
    void b1Clicked();
    void b2Clicked();
    void availableClicked();
    void cancelClicked();
    void changePasswordClicked();

private:
    Ui::Widget *ui;
    QTabWidget *tabWidget;
    int index1;                     // ѧ��combobox1
    int index2;                     // ѧ��combobox2
    int index3;                     // �γ�����combobox3
    int buttonIndex;                // �Ƿ�ѡ��

    QPushButton *button[2];
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *available[100];
    QPushButton *cancel[100];
    QPushButton *changePassword;    // �޸�����
    QLabel *welcomeLabel;

    QComboBox *combo1[2];              // ѧ��
    QComboBox *combo2[2];              // ѧ��
    QComboBox *combo3[2];              // �γ�����

    QTableWidget *choose;
    QTableWidget *courseTable;
    QTableWidget *grade;
    QTableWidget *course;

    // ����combobox���л����������ݽ��бȽ�
    string yClass;                  // ѧ��
    string tClass;                  // ѧ��

    string locate;                  // �ļ����λ��
    string adLocate;                // ����Ա��ѡ��λ��

    string studentName;             // ѧ������
    string sex;                     // ѧ���Ա�
};

#endif // WIDGET_H
