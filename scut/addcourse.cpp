#include "addcourse.h"
#include "ui_addcourse.h"
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>

AddCourse::AddCourse(TeacherWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCourse)
{
    ui->setupUi(this);
    tWidget = parent;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
}

AddCourse::~AddCourse()
{
    delete ui;
}

void AddCourse::on_pushButton_clicked()
{
    if(ui->courseName->text().trimmed().toStdString() == "" ||
       ui->studentNumber->text().trimmed().toStdString() == ""){
        QMessageBox::warning(this,"��ʾ","����д�����е�����",QMessageBox::Yes);
        return;
    }
    string cName = ui->courseName->text().trimmed().toStdString();
    string cType = ui->courseType->currentText().toStdString();
    int sNumber = atoi(ui->studentNumber->text().trimmed().toStdString().c_str());
    double cre = atoi(ui->credit->currentText().toStdString().c_str());
    string cWeek = ui->classWeek->currentText().toStdString();
    int cTime = atoi(ui->classTime->currentText().toStdString().c_str());

    // stringתint
    int week;
    int cNumber;
    if(cWeek == "����һ")
        week = 1;
    if(cWeek == "���ڶ�")
        week = 2;
    if(cWeek == "������")
        week = 3;
    if(cWeek == "������")
        week = 4;
    if(cWeek == "������")
        week = 5;
    if(cWeek == "������")
        week = 6;
    if(cWeek == "������")
        week = 7;
    if(cType == "���޿�")
        cNumber = 1000;
    if(cType == "ѡ�޿�")
        cNumber = 2000;

    for(unsigned int i=0;i<tWidget->teacher.apply.size();i++){
        int tempWeek = tWidget->teacher.apply[i].getWeek();
        int tempClassTime = tWidget->teacher.apply[i].getClassTime();
        if(tempWeek == week && tempClassTime == cTime){
            QMessageBox::warning(this,"��ʾ","ʱ����������γ̳�ͻ",QMessageBox::Yes);
            return;
        }
    }

    for(unsigned int i=0;i<tWidget->teacher.course.size();i++){
        int tempWeek = tWidget->teacher.course[i].getWeek();
        int tempClassTime = tWidget->teacher.course[i].getClassTime();
        if(tempWeek == week && tempClassTime == cTime){
            QMessageBox::warning(this,"��ʾ","ʱ������ͨ���γ̳�ͻ",QMessageBox::Yes);
            return;
        }
    }

    Course temp(sNumber,cNumber,week,cTime,cre,cName,tWidget->teacher.getName());
    tWidget->teacher.apply.push_back(temp);
    tWidget->teacher.save.push_back(temp);

    QMessageBox::warning(this,"��ʾ","�ύ�ɹ��������ĵȴ����",QMessageBox::Yes);
    tWidget->initApplyTable(tWidget->applyTable);
    close();
}

void AddCourse::on_pushButton_2_clicked()
{
    close();
}
