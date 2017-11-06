#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include <string>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTabWidget>
#include "admin.h"
using namespace std;

class AdminWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AdminWidget(Admin a,QWidget *parent = 0);

    void initApplyTable(QTableWidget *);
    void initCompulTable(QTableWidget *);
    void initElectTable(QTableWidget *);

    void delApply(string,int);
    void addCourse(string,int,Course &);

    string getTimeForClass(int,int);

    Admin admin;

signals:

public slots:
    void agreeClicked();
    void disagreeClicked();
    void fresh();
    void cMessageClicked();
    void eMessageClicked();
    void stopSelectClicked();
    void changePasswordClicked();


protected:
    void closeEvent(QCloseEvent *);

private:
    QLabel *welcomeLabel;
    string aLocate;                  // ����Ա�ļ����λ��
    string tLocate;                  // ��ʦ�ļ����λ��
    string sLocate;                  // ѧ���ļ����λ��

    QTabWidget *tabWidget;
    QPushButton *agree[100];        // ͬ�������γ�
    QPushButton *disagree[100];     // ���������γ�
    QPushButton *changePassword;    // �޸�����

    QPushButton *compulMessage[100];// ���޿�����ѧ��
    QPushButton *electMessage[100]; // ѡ�޿�����ѧ��
    QPushButton *stopSelect[100];   // ֹͣѡ��

    QTableWidget *applyTable;       // δ���Ŀγ�
    QTableWidget *compulTable;      // ��ͬ����޿γ�
    QTableWidget *electTable;       // ��ͬ��ѡ�޿γ�

};

#endif // ADMINWIDGET_H
