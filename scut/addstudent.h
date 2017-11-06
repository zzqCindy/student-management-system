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
    string time;           // 入学时间
    string majorNumber;    // 专业代号
    string classNumber;    // 班号
    int containNumber;     // 课程容纳学生最大数量
};

#endif // ADDSTUDENT_H
