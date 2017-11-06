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
        QMessageBox::warning(this,"提示","请填写完所有的内容",QMessageBox::Yes);
        return;
    }
    string cName = ui->courseName->text().trimmed().toStdString();
    string cType = ui->courseType->currentText().toStdString();
    int sNumber = atoi(ui->studentNumber->text().trimmed().toStdString().c_str());
    double cre = atoi(ui->credit->currentText().toStdString().c_str());
    string cWeek = ui->classWeek->currentText().toStdString();
    int cTime = atoi(ui->classTime->currentText().toStdString().c_str());

    // string转int
    int week;
    int cNumber;
    if(cWeek == "星期一")
        week = 1;
    if(cWeek == "星期二")
        week = 2;
    if(cWeek == "星期三")
        week = 3;
    if(cWeek == "星期四")
        week = 4;
    if(cWeek == "星期五")
        week = 5;
    if(cWeek == "星期六")
        week = 6;
    if(cWeek == "星期天")
        week = 7;
    if(cType == "必修课")
        cNumber = 1000;
    if(cType == "选修课")
        cNumber = 2000;

    for(unsigned int i=0;i<tWidget->teacher.apply.size();i++){
        int tempWeek = tWidget->teacher.apply[i].getWeek();
        int tempClassTime = tWidget->teacher.apply[i].getClassTime();
        if(tempWeek == week && tempClassTime == cTime){
            QMessageBox::warning(this,"提示","时间与已申请课程冲突",QMessageBox::Yes);
            return;
        }
    }

    for(unsigned int i=0;i<tWidget->teacher.course.size();i++){
        int tempWeek = tWidget->teacher.course[i].getWeek();
        int tempClassTime = tWidget->teacher.course[i].getClassTime();
        if(tempWeek == week && tempClassTime == cTime){
            QMessageBox::warning(this,"提示","时间与已通过课程冲突",QMessageBox::Yes);
            return;
        }
    }

    Course temp(sNumber,cNumber,week,cTime,cre,cName,tWidget->teacher.getName());
    tWidget->teacher.apply.push_back(temp);
    tWidget->teacher.save.push_back(temp);

    QMessageBox::warning(this,"提示","提交成功，请耐心等待结果",QMessageBox::Yes);
    tWidget->initApplyTable(tWidget->applyTable);
    close();
}

void AddCourse::on_pushButton_2_clicked()
{
    close();
}
