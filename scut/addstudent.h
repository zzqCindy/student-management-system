#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QDialog>
#include <compulmessage.h>

namespace Ui {
    class AddStudent;
}

class AddStudent : public QDialog
{
    Q_OBJECT

public:
    explicit AddStudent(CompulMessage *parent);
    ~AddStudent();

private slots:
    void on_cancel_clicked();

    void on_ok_clicked();

private:
    Ui::AddStudent *ui;
    CompulMessage *cMessage;
    string time;           // ��ѧʱ��
    string majorNumber;    // רҵ����
    string classNumber;    // ���
    int containNumber;     // �γ�����ѧ���������
};

#endif // ADDSTUDENT_H
