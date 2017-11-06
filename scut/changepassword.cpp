#include "changepassword.h"
#include "ui_changepassword.h"
#include <fstream>
#include <QMessageBox>
#include <QTextCodec>
#include <QDebug>
#include <windows.h>
using namespace std;

ChangePassword::ChangePassword(int i,string un,string pw,QWidget *parent) :
    QDialog(parent),
    index(i),
    userNumber(un),
    userPassword(pw),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);
    ui->oldPassword->setEchoMode(QLineEdit::Password);
    ui->newPassword->setEchoMode(QLineEdit::Password);
    ui->surePassword->setEchoMode(QLineEdit::Password);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GB2312"));
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_yes_clicked()
{
    string newPw,oldPw,surePw;
    QByteArray ba1 = ui->oldPassword->text().trimmed().toLatin1();
    QByteArray ba2 = ui->newPassword->text().trimmed().toLatin1();
    QByteArray ba3 = ui->surePassword->text().trimmed().toLatin1();
    oldPw=ba1.data();
    newPw=ba2.data();
    surePw=ba3.data();

    if(oldPw != userPassword){
        QMessageBox::warning(this,"Warning","密码错误!",QMessageBox::Yes);

        ui->oldPassword->clear();
        ui->newPassword->clear();
        ui->surePassword->clear();
        ui->oldPassword->setFocus();
        return;
    }

    if(newPw != surePw){
        QMessageBox::warning(this,"Warning","两次输入密码不一样!",QMessageBox::Yes);

        ui->oldPassword->clear();
        ui->newPassword->clear();
        ui->surePassword->clear();
        ui->oldPassword->setFocus();
        return;
    }

    string location = "E:\\Qt\\scutStatistic\\";
    int count;
    string user = "";
    string str = "";

    // 修改密码
    switch(index){
        case 0:{
            location += "admin\\login";
            int i=0;
            fstream adminPw1((location+".txt").c_str());
            fstream adminPw2((location+"temp.txt").c_str(),ios::out|ios::trunc);
            while(user != "-1"){
                adminPw1 >> user;
                if(user == userNumber)
                    count = i;
                if(user == "-1"){
                    adminPw2 << user;
                    break;
                }
                i++;
                getline(adminPw1,str);
                adminPw2 << user << " " << str << endl;
            }
            adminPw1.close();
            adminPw2.close();

            i=0;
            str = "";
            fstream adminPw3((location+".txt").c_str(),ios::out|ios::trunc);
            fstream adminPw4((location+"temp.txt").c_str());
            while(str != "-1"){
                getline(adminPw4,str);
                if(i == count)
                    adminPw3 << userNumber << " " << newPw << '\n';
                else
                    adminPw3 << str << endl;
                i++;
            }
            adminPw3.close();
            adminPw4.close();
            WinExec(("cmd /c del "+location+"temp.txt").c_str(), SW_HIDE);}
            break;
        case 1:{
            location += "teacher\\login";
            int i=0;
            fstream teaPw1((location+".txt").c_str());
            fstream teaPw2((location+"temp.txt").c_str(),ios::out|ios::trunc);
            while(user != "-1"){
                teaPw1 >> user;
                if(user == userNumber)
                    count = i;
                if(user == "-1"){
                    teaPw2 << user;
                    break;
                }
                i++;
                getline(teaPw1,str);
                teaPw2 << user << " " << str << endl;
            }
            teaPw1.close();
            teaPw2.close();

            i=0;
            str = "";
            string user = "",pw = "";
            fstream teaPw3((location+".txt").c_str(),ios::out|ios::trunc);
            fstream teaPw4((location+"temp.txt").c_str());
            while(str != "-1"){
                teaPw4 >> user;
                if(user == "-1"){
                    teaPw4 << user;
                    break;
                }
                teaPw4 >> pw >> str;
                if(i == count)
                    teaPw3 << userNumber << " " << newPw << " " << str << '\n';
                else
                    teaPw3 << user << " " << pw << " " << str << endl;
                i++;
            }
            teaPw3.close();
            teaPw4.close();
            WinExec(("cmd /c del "+location+"temp.txt").c_str(), SW_HIDE);}
            break;
        case 2:{
            string temp = "";
            location += "student\\" + temp.assign(userNumber,4,1) + "\\login";
            int i=0;
            fstream stuPw1((location+".txt").c_str());
            fstream stuPw2((location+"temp.txt").c_str(),ios::out|ios::trunc);
            while(user != "-1"){
                stuPw1 >> user;
                if(user == userNumber)
                    count = i;
                if(user == "-1"){
                    stuPw2 << user;
                    break;
                }
                i++;
                getline(stuPw1,str);
                stuPw2 << user << " " << str << endl;
            }
            stuPw1.close();
            stuPw2.close();

            i=0;
            str = "";
            fstream stuPw3((location+".txt").c_str(),ios::out|ios::trunc);
            fstream stuPw4((location+"temp.txt").c_str());
            while(str != "-1"){
                getline(stuPw4,str);
                if(i == count)
                    stuPw3 << userNumber << " " << newPw << " "
                           << str.assign(userNumber,0,4) << " "
                           << userNumber[4] << " "
                           << userNumber[5] << '\n';
                else
                    stuPw3 << str << endl;
                i++;
            }
            stuPw3.close();
            stuPw4.close();
            WinExec(("cmd /c del "+location+"temp.txt").c_str(), SW_HIDE);}
            break;
    }


    QMessageBox::warning(this,"提示","修改成功!",QMessageBox::Yes);
    accept();
}

void ChangePassword::on_cancel_clicked()
{
    close();
}
