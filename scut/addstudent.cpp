#include "addstudent.h"
#include "ui_addstudent.h"
#include <sstream>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QTextCodec>
#include <QDebug>
#include <windows.h>

AddStudent::AddStudent(CompulMessage *parent) :
    QDialog(parent),
    ui(new Ui::AddStudent)
{
    ui->setupUi(this);
    cMessage = parent;
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));

    string location = "E:\\Qt\\scutStatistic\\student\\";
    string str = "";
    fstream mList((location+"list.txt").c_str());
    while(str != "-1"){
        mList >> str;
        if(str != "-1")
            ui->mNumber->addItem(str.c_str());
        if(str == "-1")
            break;
        fstream sList((location+str+"\\login.txt").c_str());
        string user,pw,mn;
        int cy,cn;
        user = "";
        int temp1=-1,temp2=-1;
        while(user != "-1"){
            sList >> user;
            if(user == "-1")
                break;
            sList >> pw >> cy >> mn >> cn;
            // 设置入学年份
            if(temp1 == -1 || temp1 != cy){
                temp1 = cy;
                stringstream ss;
                string temp3;
                ss << temp1;
                ss >> temp3;
                int flag = 0;
                for(int i =0;i<ui->cYear->count();i++){
                    if(temp3 == (ui->cYear->itemText(i)).toStdString()){
                        flag = 1;
                        break;
                    }
                }
                if(!flag)
                    ui->cYear->addItem(temp3.c_str());
            }
            // 设置班别
            if(temp2 == -1 || temp2 != cn){
                temp2 = cn;
                stringstream ss;
                string temp3;
                ss << temp2;
                ss >> temp3;
                int flag = 0;
                for(int i =0;i<ui->cNumber->count();i++){
                    if(temp3 == (ui->cNumber->itemText(i)).toStdString()){
                        flag = 1;
                        break;
                    }
                }
                if(!flag)
                    ui->cNumber->addItem(temp3.c_str());
            }
        }
        sList.close();
    }
    mList.close();

}

AddStudent::~AddStudent()
{
    delete ui;
}

void AddStudent::on_cancel_clicked()
{
    close();
}

void AddStudent::on_ok_clicked()
{
    majorNumber = ui->mNumber->currentText().toStdString();
    time = ui->cYear->currentText().toStdString();
    classNumber = ui->cNumber->currentText().toStdString();
    containNumber = cMessage->course.getStudentNumber();

    // 是否有重复
    for(int i=0;i<cMessage->sTable->rowCount();i++){
        string mNumber = cMessage->sTable->item(i,0)->text().toStdString();
        string year = cMessage->sTable->item(i,1)->text().toStdString();
        string cNumber = cMessage->sTable->item(i,2)->text().toStdString();
        if(majorNumber == mNumber && time == year && classNumber == cNumber){
            QMessageBox::warning(this,"Warning","该班级已被添加！",QMessageBox::Yes);
            return ;
        }
    }

    string location = "E:\\Qt\\scutStatistic\\student\\"+majorNumber+"\\" +
            time + "\\" + classNumber + "\\";
    QDir *check = new QDir;
    bool exist;

    // 判断是否超过人数
    string curNumString = time + majorNumber + classNumber + "01";
    int curNum = atoi(curNumString.c_str());
    for(curNum; curNum>0; curNum++){
        stringstream ss;
        ss << curNum;
        string tempNumber;
        ss >> tempNumber;
        exist = check->exists((location+tempNumber).c_str());
        if(!exist)
            break;
    }
    int curNumber = curNum - atoi(curNumString.c_str());
    if(curNumber+cMessage->currentNumber > containNumber){
        QMessageBox::warning(this,"Warning","人数超过限制！",QMessageBox::Yes);
        return;
    }

    // 是否添加
    QMessageBox msg;
    msg.setWindowTitle("提示");
    msg.setIcon(QMessageBox::Information);
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setInformativeText("是否继续？");
    msg.setText("添加完成后不可删除");
    int rec = msg.exec();
    switch(rec){
        case QMessageBox::Yes:
            break;
        case QMessageBox::Cancel:
            return;
    }

    // 成功添加
    location =  "E:\\Qt\\scutStatistic\\admin\\compulsory\\";
    string str = "";
    string courseClassNumber;
    stringstream s0;
    s0 << cMessage->course.getClassNumber();
    s0 >> courseClassNumber;

    fstream add1((location+courseClassNumber+".txt").c_str());
    fstream add2((location+"temp.txt").c_str(),ios::out|ios::trunc);
    while(str != "-1"){
        getline(add1,str);
        add2 << str << endl;
    }
    add1.close();
    add2.close();

    str = "";
    fstream add3((location+courseClassNumber+".txt").c_str(),ios::out|ios::trunc);
    fstream add4((location+"temp.txt").c_str());
    while(str != "-1"){
        qDebug() << str.c_str();
        getline(add4,str);
        if(str == "-1"){
            add3 << majorNumber << " " << time << " " << classNumber << '\n';
        }
        add3 << str << endl;
    }
    add3.close();
    add4.close();
    WinExec(("cmd /c del "+location+"temp.txt").c_str(), SW_HIDE);

    // 将该course加入至对应班级
    str = "";
    location = "E:\\Qt\\scutStatistic\\student\\" + majorNumber + "\\" + time + "\\"
           + classNumber + "\\";

    fstream sCom1((location+"compulsory.txt").c_str());
    fstream sCom2((location+"temp.txt").c_str(),ios::trunc|ios::out);
    while(str != "-1"){
        getline(sCom1,str);
        sCom2 << str << endl;
    }
    sCom1.close();
    sCom2.close();

    str = "";
    fstream sCom3((location+"compulsory.txt").c_str(),ios::trunc|ios::out);
    fstream sCom4((location+"temp.txt").c_str());
    while(str != "-1"){
        getline(sCom4,str);
        if(str == "-1"){
            sCom3 << cMessage->course.getClassNumber() << " "
                  << cMessage->course.getStudentNumber() << " "
                  << cMessage->course.getWeek() << " "
                  << cMessage->course.getClassTime() << " "
                  << cMessage->course.getCredit() << " "
                  << cMessage->course.getClassName() << " "
                  << cMessage->course.getTeacher() << " "
                  << "2015 1 -1 -1\n";
        }
        sCom3 << str << endl;
    }
    sCom3.close();
    sCom4.close();
    WinExec(("cmd /c del "+location+"temp.txt").c_str(), SW_HIDE);

    QMessageBox::warning(this,"提示","提交成功",QMessageBox::Yes);
    cMessage->initTable(cMessage->sTable);
    close();
}
