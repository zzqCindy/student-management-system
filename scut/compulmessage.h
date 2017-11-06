#ifndef COMPULMESSAGE_H
#define COMPULMESSAGE_H

#include "adminwidget.h"

#include <QDialog>

namespace Ui {
    class CompulMessage;
}

class CompulMessage : public QDialog
{
    Q_OBJECT

public:
    explicit CompulMessage(AdminWidget *parent,Course &course,int currentNumber = 0);
    CompulMessage(int classNumber,int type = 0,QWidget *parent = 0,int currentNumber=0);
    ~CompulMessage();

    void initialize();
    void initTable(QTableWidget *);
    void initWidget();

    int classNumber;        //�γ̴���
    int currentNumber;      //����ѧ������
    string location;
    Course course;
    QTableWidget *sTable;

public slots:
    void onBackClicked();
    void onAddClicked();
    void onDetailClicked();
    void onSetGradeClicked();

private:
    Ui::CompulMessage *ui;
    AdminWidget *aWidget;
    QPushButton *back;
    QPushButton *add;
    QPushButton *detail[100];
    QPushButton *setGrade[100];

    QLabel *curNumber;
    int type;               //1Ϊ���óɼ�
};

#endif // COMPULMESSAGE_H
